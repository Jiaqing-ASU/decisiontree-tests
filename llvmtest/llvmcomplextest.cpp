#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include <cassert>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace llvm;
using namespace std;

int main() {
    LLVMContext Context;
 // Create some module to put our function into it.
    unique_ptr<Module> Owner = make_unique<Module>("ruletest", Context);
    Module *M = Owner.get();
    
 // Create the function entry and insert this entry into module M.
 // The function will have a return type of "int" and take an argument of "int*".
    Function *F =
        Function::Create(FunctionType::get(Type::getInt32Ty(Context),{Type::getInt32PtrTy(Context)}, false),Function::ExternalLinkage, "rules", M);

 // Add a basic block to the function.
    BasicBlock *BB = BasicBlock::Create(Context, "entry", F);

 // Add more blocks to be used by br command.
    BasicBlock *BB1 = BasicBlock::Create(Context,"label1", F);
    BasicBlock *BB2 = BasicBlock::Create(Context,"label2");
    BasicBlock *BB3 = BasicBlock::Create(Context,"label3");
    
 // Create a basic block builder with default parameters.
 // The builder will automatically append instructions to the basic block BB.
    IRBuilder<> builder(BB);
 // Set some values from the rule.
    Value *nodeValue_1 = builder.getInt32(2);
    Value *nodeValue_2 = builder.getInt32(4);
    Value *trueReturn = builder.getInt32(2);
    Value *falseReturn = builder.getInt32(-1);
 // Get pointers to the integer argument of the add1 function.
    assert(F->arg_begin() != F->arg_end()); // Make sure there's an arg
    Argument *givenArray = &*F->arg_begin(); // Get the arg
    
 // Do the compare in the first block using the first rule.
    Value* givenValue_1 = builder.CreateLoad(givenArray);
    Value *cond_1 = builder.CreateICmp(CmpInst::Predicate::ICMP_SLT, givenValue_1, nodeValue_1);
    builder.CreateCondBr(cond_1,BB1,BB2);
    
 // Do the compare in the second block using the second rule.
    builder.SetInsertPoint(BB1);
    Value* givenStart_2 = builder.CreateConstInBoundsGEP1_64(Type::getInt32Ty(Context),givenArray,1);
    Value* givenValue_2 = builder.CreateLoad(givenStart_2);
    Value *cond_2 = builder.CreateICmp(CmpInst::Predicate::ICMP_EQ, givenValue_2, nodeValue_2);
    builder.CreateCondBr(cond_2,BB3,BB2);
    
 // Jump to the return block.
    F->getBasicBlockList().push_back(BB2);
    builder.SetInsertPoint(BB2);
    builder.CreateBr(BB3);
    
 // Return block.
    F->getBasicBlockList().push_back(BB3);
    builder.SetInsertPoint(BB3);
    PHINode *PN = builder.CreatePHI(Type::getInt32Ty(Context), 2);
    PN->addIncoming(trueReturn,BB1);
    PN->addIncoming(falseReturn,BB2);
    builder.CreateRet(PN);
    
    outs() << "We just constructed this LLVM module:\n\n" << *M;
    outs().flush();
    std::error_code ec;
    llvm::raw_fd_ostream os("complextest.bc", ec);
    WriteBitcodeToFile(*M, os);
    os.flush();
    return 0;
}