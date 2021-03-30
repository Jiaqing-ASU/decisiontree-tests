#include "KaleidoscopeJIT.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace llvm;
using namespace llvm::orc;

// LLVM
static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
// JIT
static std::unique_ptr<KaleidoscopeJIT> TheJIT;

int main(int argc, char *argv[]){
    
    char *p;
    long conv = strtol(argv[3], &p, 10);
    long nodevalue = strtol(argv[1], &p, 10);
    long givenvalue = strtol(argv[2], &p, 10);
    // printf("%ld\t",conv);
    // printf("%d\t",argc);
    
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    
    // Module Initialization
    TheModule = llvm::make_unique<Module>("jit", TheContext);

    // Used to be runned by JIT later
    TheJIT = llvm::make_unique<KaleidoscopeJIT>();
    TheModule->setDataLayout(TheJIT->getTargetMachine().createDataLayout());

    // Define the args
    vector<std::string> ArgNames;

    // Function mycmp has 2 args
    ArgNames.push_back(string("givenvalue"));
    ArgNames.push_back(string("nodevalue"));

    // Make the 2 args attach to LLVM Type::double
    std::vector<Type *> Doubles(ArgNames.size(), Type::getDoubleTy(TheContext));

    // Generate LLVM function type
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(TheContext), Doubles, false);

    // Create function whose FunctionType is FT
    Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "decisionrule", TheModule.get());

    // Give the name of Function args and save the args as innerargs
    unsigned Idx = 0;

    std::vector<Value *>innerargs;

    for (auto &Arg : TheFunction->args()) {
        Arg.setName(ArgNames[Idx++]);
        innerargs.push_back(&Arg);
    }

    // 4 blocks
    // First is function's entry
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", TheFunction);

    // Generate LLVM function body:control-flow
    // At least three blocks(MergeBB is not necessary)
    // If's cond  if(a > b)
    // The if expression belongs to BB
    
	// BB:
	//   if xxx then
	//        then-logic
	//   else
	//        else-logic
    Builder.SetInsertPoint(BB);
    Value *nodeValue = ConstantFP::get(TheContext, APFloat((double)nodevalue));
    
    Value *cond;
    
    if(conv==1){
        cond = Builder.CreateFCmpULT(nodeValue, innerargs[0], "cmptmp");
    }else if (conv==2){
        cond = Builder.CreateFCmpOEQ(nodeValue, innerargs[0], "cmptmp");
    }else{
        cond = Builder.CreateFCmpULT(innerargs[0], nodeValue, "cmptmp");
    }
    
    // Then block
    BasicBlock *ThenBB = BasicBlock::Create(TheContext, "then", TheFunction);
    // Else block
    BasicBlock *ElseBB = BasicBlock::Create(TheContext, "else");

    // After control block
    BasicBlock *MergeBB = BasicBlock::Create(TheContext, "ifcont");

    // Join three block
    Builder.CreateCondBr(cond, ThenBB, ElseBB);

    // Then expression
    // Then:
    //    then-logic = ThenV
    //    goto MergeBB
    Builder.SetInsertPoint(ThenBB);
    Value *ThenV = ConstantFP::get(TheContext, APFloat(1.0));

    // Builder.CreateRet(ThenV);
    // We also could just CreateRet not CreateBr.
    Builder.CreateBr(MergeBB);

    // ElseBB has not been inserted because ElseBB doesn't 
    // Created by Thefunction
    TheFunction->getBasicBlockList().push_back(ElseBB);

    // Else expression and goto MergeBB
    // Else:
    //    else-logic = ElseV
    //    goto MergeBB
    Builder.SetInsertPoint(ElseBB);
    Value *ElseV = ConstantFP::get(TheContext, APFloat(0.0));
    // Builder.CreateRet(ElseV);
    Builder.CreateBr(MergeBB);

    // MergeBB has not been inserted
    TheFunction->getBasicBlockList().push_back(MergeBB);

    // Newly created code will go into the “merge” block
    // Ifcont
    Builder.SetInsertPoint(MergeBB);

    // Need to construct MergeBB
    PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");

	// If from ThenBB then ph is ThenV
	// If from ElseBB then ph is ElseV
    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);

    Builder.CreateRet(PN);
    
    cout << "We just constructed this LLVM module:\n\n";
    // Print LLVM IR
    TheFunction->print(errs());
    
    // Use JIT to run the code
    auto H = TheJIT->addModule(std::move(TheModule));
    auto ExprSymbol = TheJIT->findSymbol("decisionrule");
    double (*decisionrule)(double) = (double (*)(double))(intptr_t)cantFail(ExprSymbol.getAddress());
    cout << "\nRunning decisionrule: ";
    cout << "Result: " << decisionrule(givenvalue) << endl;
}