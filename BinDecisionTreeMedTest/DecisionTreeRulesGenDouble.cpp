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
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <exception> 
#include <sstream>

using namespace llvm;
using namespace std;

int main(int argc, const char *argv[])
{
	int lineNumber = 0; //numbers of lines in the input
	int blockNumber = 0; //numbers of blocks will be generated in the llvm IR
	double trueReturnArray; //return value if the rules all true
	double falseReturnArray; //return value if at least one rule is false
	string inputFilePath = argv[1]; //input rules path
	ifstream inFile(inputFilePath, ios::in);
	string lineString;
	vector<string> lineArray;
	vector<int> positionArray;
	vector<double> valueArray;
	vector<string> compareArray;
	while (getline(inFile, lineString))
	{
		stringstream ss(lineString);
		string str;
		lineNumber += 1;
		while (getline(ss, str, ',')){
			lineArray.push_back(str);
		}
	}
	if (lineNumber == 2){
		blockNumber = 1;
	}else{
		blockNumber = lineNumber + 1;
	}
	cout << "Number of blocks need to be generate: " << blockNumber << endl;
	for (int i = 0; i < lineArray.size(); i++){
        if(i == 0){
        	stringstream ss;
        	ss << lineArray.at(i);
        	ss >> trueReturnArray;
        }
        else if(i == 1){
        	stringstream ss;
        	ss << lineArray.at(i);
        	ss >> falseReturnArray;
        }
        else if(i%3 == 0){
        	stringstream ss;
        	double thisValue;
        	ss << lineArray.at(i);
        	ss >> thisValue;
        	valueArray.push_back(thisValue);
        }
        else if(i%3 == 1){
        	compareArray.push_back(lineArray.at(i));
        }
        else if(i%3 == 2){
        	stringstream ss;
        	int thisValue;
        	ss << lineArray.at(i);
        	ss >> thisValue;
        	positionArray.push_back(thisValue);
        }
        else{
        	cout << "Error analysis input rules" << endl;
        }
	}

	cout << "All true will return: " << trueReturnArray << endl;
	cout << "At least one false will return: " << falseReturnArray << endl;
	cout << "Compare values" << endl;
	for (int i = 0; i < valueArray.size(); i++){
		cout << valueArray.at(i) << endl;
	}
	cout << "Compare positions" << endl;
	for (int i = 0; i < positionArray.size(); i++){
		cout << positionArray.at(i) << endl;
	}
	cout << "Compare symbols" << endl;
	for (int i = 0; i < compareArray.size(); i++){
		cout << compareArray.at(i) << endl;
	}

	LLVMContext Context;
 	// Create some module to put our function into it.
    unique_ptr<Module> Owner = make_unique<Module>(argv[2], Context);
    Module *M = Owner.get();
	
	if(blockNumber == 1){
		// Only do one comparison
		// Create the function entry and insert this entry into module M.
		// The function will have a return type of "double" and take an argument of "double*".
		Function *F = 
			Function::Create(FunctionType::get(Type::getDoubleTy(Context),{Type::getDoublePtrTy(Context)}, false),Function::ExternalLinkage, "rules", M);
		// Add a basic block to the function. As before, it automatically inserts because of the last argument.
		BasicBlock *BB = BasicBlock::Create(Context, "entry", F);

		// Create a basic block builder with default parameters.
 		// The builder will automatically append instructions to the basic block BB.
    	IRBuilder<> builder(BB);
 		// Set some values from the rule.

 		Value *nodeValue = ConstantFP::get(Context, APFloat(valueArray.at(0)));
    	Value *trueReturn = ConstantFP::get(Context, APFloat(trueReturnArray));
    	Value *falseReturn = ConstantFP::get(Context, APFloat(falseReturnArray));

 		// Get pointers to the integer argument of the function.
    	assert(F->arg_begin() != F->arg_end()); // Make sure there's an argument.
    	Argument *givenArray = &*F->arg_begin(); // Get the argument.
    	
 		// Create the add instruction, inserting it into the end of BB.
    	Value* givenStart = builder.CreateConstInBoundsGEP1_64(Type::getDoubleTy(Context),givenArray,positionArray.at(0));
    	Value* givenValue = builder.CreateLoad(givenStart);
    	Value *cond;
    	if (compareArray.at(0) == "="){
    		cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OEQ, givenValue, nodeValue);
    	}else if (compareArray.at(0) == "!="){
    		cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_ONE, givenValue, nodeValue);
    	}else if (compareArray.at(0) == ">"){
    		cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OGT, givenValue, nodeValue);
    	}else if (compareArray.at(0) == ">="){
    		cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OGE, givenValue, nodeValue);
    	}else if (compareArray.at(0) == "<"){
    		cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OLT, givenValue, nodeValue);
    	}else if (compareArray.at(0) == "<="){
    		cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OLE, givenValue, nodeValue);
    	}
    	Value *select = builder.CreateSelect(cond, trueReturn, falseReturn);
 		// Create the return instruction and add it to the basic block.
    	builder.CreateRet(select);
	}else{
		// More than one comparison.
		// Create the function entry and insert this entry into module M.
 		// The function will have a return type of "double" and take an argument of "double*".
    	Function *F =
        	Function::Create(FunctionType::get(Type::getDoubleTy(Context),{Type::getDoublePtrTy(Context)}, false),Function::ExternalLinkage, "rules", M);

        // If more than one rule needs to be compared, the Values and Blocks used for comparison need to be saved in the vector.
        vector<BasicBlock*> BasicBlockArray;
        vector<Value*> ValueIRArray;

        // Add a basic block and rule blocks into the function.
        for (int i = 0; i < blockNumber-2; i++){
        	BasicBlockArray.push_back(BasicBlock::Create(Context, "BB" + to_string(i), F));
    	}
    	// Add 2 blocks for thr final return value.
    	for (int i = blockNumber-2; i < blockNumber; i++){
    		BasicBlockArray.push_back(BasicBlock::Create(Context, "BB" + to_string(i)));
    	}

 		// Create a basic block builder with default parameters.
 		// The builder will automatically append instructions to the basic block BB.
    	IRBuilder<> builder(BasicBlockArray.at(0));

 		// Set some values from the rule.
    	for (int i = 0; i < valueArray.size(); i++){
    		ValueIRArray.push_back(ConstantFP::get(Context, APFloat(valueArray.at(i))));
    	}

    	// Set true and false return values from the rule.
    	Value *trueReturn = ConstantFP::get(Context, APFloat(trueReturnArray));
    	Value *falseReturn = ConstantFP::get(Context, APFloat(falseReturnArray));
 		// Get pointers to the integer argument of the function.
    	assert(F->arg_begin() != F->arg_end()); // Make sure there's an argument.
    	Argument *givenArray = &*F->arg_begin(); // Get the argument.

    	//Add operations into rule blocks in the function.
    	for (int i = 0; i < blockNumber-2; i++){
    		if (i != 0){
    			builder.SetInsertPoint(BasicBlockArray.at(i));
    		}
    		Value* givenStart = builder.CreateConstInBoundsGEP1_64(Type::getDoubleTy(Context),givenArray,positionArray.at(i));
    		Value* givenValue = builder.CreateLoad(givenStart);
    		// Do the compare in the block using corresponding rule.
			Value *cond;
			if (compareArray.at(i) == "="){
    			cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OEQ, givenValue, ValueIRArray.at(i));
    		}else if (compareArray.at(i) == "!="){
    			cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_ONE, givenValue, ValueIRArray.at(i));
    		}else if (compareArray.at(i) == ">"){
    			cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OGT, givenValue, ValueIRArray.at(i));
    		}else if (compareArray.at(i) == ">="){
    			cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OGE, givenValue, ValueIRArray.at(i));
    		}else if (compareArray.at(i) == "<"){
    			cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OLT, givenValue, ValueIRArray.at(i));
    		}else if (compareArray.at(i) == "<="){
    			cond = builder.CreateFCmp(CmpInst::Predicate::FCMP_OLE, givenValue, ValueIRArray.at(i));
    		}
    		if (i == blockNumber-3){
    			builder.CreateCondBr(cond,BasicBlockArray.at(blockNumber-1),BasicBlockArray.at(blockNumber-2));
    		}else{
    			builder.CreateCondBr(cond,BasicBlockArray.at(i+1),BasicBlockArray.at(blockNumber-2));
    		}
    	}

    	// Jump to the return block.
    	F->getBasicBlockList().push_back(BasicBlockArray.at(blockNumber-2));
    	builder.SetInsertPoint(BasicBlockArray.at(blockNumber-2));
    	builder.CreateBr(BasicBlockArray.at(blockNumber-1));
    
		// Return block.
    	F->getBasicBlockList().push_back(BasicBlockArray.at(blockNumber-1));
    	builder.SetInsertPoint(BasicBlockArray.at(blockNumber-1));
    	PHINode *PN = builder.CreatePHI(Type::getDoubleTy(Context), 2);
    	PN->addIncoming(trueReturn,BasicBlockArray.at(blockNumber-3));
    	PN->addIncoming(falseReturn,BasicBlockArray.at(blockNumber-2));
    	builder.CreateRet(PN);
	}
	
	outs() << "We just constructed this LLVM module:\n\n" << *M;
    outs().flush();
    std::error_code ec;
    llvm::raw_fd_ostream os(argv[3], ec);
    WriteBitcodeToFile(*M, os);
    os.flush();
	return 0;
}