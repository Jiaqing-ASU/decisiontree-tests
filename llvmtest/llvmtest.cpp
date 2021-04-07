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
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

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
        Function::Create(FunctionType::get(Type::getInt32Ty(Context),{Type::getInt32PtrTy(Context)}, false),Function::ExternalLinkage, "testDataOnDecisionTreeRules", M);

 // Add a basic block to the function. As before, it automatically inserts because of the last argument.
    BasicBlock *BB = BasicBlock::Create(Context, "entry", F);
    
 // Create a basic block builder with default parameters.
 // The builder will automatically append instructions to the basic block BB.
    IRBuilder<> builder(BB);
 // Set some values from the rule.
    Value *nodeValue = builder.getInt32(4);
    Value *trueReturn = builder.getInt32(2);
    Value *falseReturn = builder.getInt32(-1);
 // Get pointers to the integer argument of the add1 function.
    assert(F->arg_begin() != F->arg_end()); // Make sure there's an arg
    Argument *givenArray = &*F->arg_begin(); // Get the arg
    
 // Create the add instruction, inserting it into the end of BB.
    Value* givenStart = builder.CreateConstInBoundsGEP1_64(Type::getInt32Ty(Context),givenArray,1);
    Value* givenValue = builder.CreateLoad(givenStart);
    Value *cond = builder.CreateICmp(CmpInst::Predicate::ICMP_EQ, givenValue, nodeValue);
    Value *select = builder.CreateSelect(cond, trueReturn, falseReturn);
 // Create the return instruction and add it to the basic block
    builder.CreateRet(select);
    
    outs() << "We just constructed this LLVM module:\n\n" << *M;
    outs().flush();
    std::error_code ec;
    llvm::raw_fd_ostream os("test.bc", ec);
    WriteBitcodeToFile(*M, os);
    os.flush();
    return 0;
}