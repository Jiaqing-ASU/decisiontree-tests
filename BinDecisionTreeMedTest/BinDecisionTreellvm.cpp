#include "header.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/Support/MemoryBuffer.h>
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/DynamicLibrary.h>
#include "llvm/Support/Debug.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/iterator_range.h"
#include "llvm/ADT/ArrayRef.h"
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
using namespace llvm;
using namespace orc;

RTDyldMemoryManager* RTDyldMM = NULL;

typedef double (*func_type)(double*);

ExecutionEngine* initEE(std::unique_ptr<Module> Owner) {
    ExecutionEngine* EE = NULL;
    string ErrStr;
    if (EE == NULL) {
        RTDyldMM = new SectionMemoryManager();
        EE = EngineBuilder(std::move(Owner))
            .setEngineKind(EngineKind::JIT)
            .setErrorStr(&ErrStr)
            .setVerifyModules(true)
            .setMCJITMemoryManager(std::unique_ptr<RTDyldMemoryManager>(RTDyldMM))
            .setOptLevel(CodeGenOpt::Default)
            .create();

    } else
        EE->addModule(std::move(Owner));
    if (ErrStr.length() != 0)
        cerr << "Create Engine Error\n" << endl << ErrStr << endl;
    EE->finalizeObject();
    return EE;
}

int main(int argc, const char *argv[])
{
    clock_t start,end;
    msd mresult;
    mresult["B"] = 2.0;
    mresult["M"] = 1.0;
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    LLVMContext context;
    SMDiagnostic error;
    unique_ptr<Module> Owner_1 = parseIRFile("rule1.bc", error, context);
    unique_ptr<Module> Owner_2 = parseIRFile("rule2.bc", error, context);
    unique_ptr<Module> Owner_3 = parseIRFile("rule3.bc", error, context);
    unique_ptr<Module> Owner_4 = parseIRFile("rule4.bc", error, context);
    unique_ptr<Module> Owner_5 = parseIRFile("rule5.bc", error, context);
    unique_ptr<Module> Owner_6 = parseIRFile("rule6.bc", error, context);
    unique_ptr<Module> Owner_7 = parseIRFile("rule7.bc", error, context);
    unique_ptr<Module> Owner_8 = parseIRFile("rule8.bc", error, context);
    unique_ptr<Module> Owner_9 = parseIRFile("rule9.bc", error, context);
    unique_ptr<Module> Owner_10 = parseIRFile("rule10.bc", error, context);
    unique_ptr<Module> Owner_11 = parseIRFile("rule11.bc", error, context);
    unique_ptr<Module> Owner_12 = parseIRFile("rule12.bc", error, context);
    unique_ptr<Module> Owner_13 = parseIRFile("rule13.bc", error, context);
    unique_ptr<Module> Owner_14 = parseIRFile("rule14.bc", error, context);
    unique_ptr<Module> Owner_15 = parseIRFile("rule15.bc", error, context);
    unique_ptr<Module> Owner_16 = parseIRFile("rule16.bc", error, context);
    if(Owner_1 == nullptr || Owner_2 == nullptr || Owner_3 == nullptr || Owner_4 == nullptr || Owner_5 == nullptr || 
        Owner_6 == nullptr || Owner_7 == nullptr || Owner_8 == nullptr || Owner_9 == nullptr || Owner_10 == nullptr || 
        Owner_11 == nullptr || Owner_12 == nullptr || Owner_13 == nullptr || Owner_14 == nullptr || 
        Owner_15 == nullptr || Owner_16 == nullptr) {
        cout << "Load Bitcode Files Error\n" << endl;
        return 0;
    }
    Module *M1 = Owner_1.get();
    Module *M2 = Owner_2.get();
    Module *M3 = Owner_3.get();
    Module *M4 = Owner_4.get();
    Module *M5 = Owner_5.get();
    Module *M6 = Owner_6.get();
    Module *M7 = Owner_7.get();
    Module *M8 = Owner_8.get();
    Module *M9 = Owner_9.get();
    Module *M10 = Owner_10.get();
    Module *M11 = Owner_11.get();
    Module *M12 = Owner_12.get();
    Module *M13 = Owner_13.get();
    Module *M14 = Owner_14.get();
    Module *M15 = Owner_15.get();
    Module *M16 = Owner_16.get();
    ExecutionEngine* EE1 = initEE(std::move(Owner_1));
    ExecutionEngine* EE2 = initEE(std::move(Owner_2));
    ExecutionEngine* EE3 = initEE(std::move(Owner_3));
    ExecutionEngine* EE4 = initEE(std::move(Owner_4));
    ExecutionEngine* EE5 = initEE(std::move(Owner_5));
    ExecutionEngine* EE6 = initEE(std::move(Owner_6));
    ExecutionEngine* EE7 = initEE(std::move(Owner_7));
    ExecutionEngine* EE8 = initEE(std::move(Owner_8));
    ExecutionEngine* EE9 = initEE(std::move(Owner_9));
    ExecutionEngine* EE10 = initEE(std::move(Owner_10));
    ExecutionEngine* EE11 = initEE(std::move(Owner_11));
    ExecutionEngine* EE12 = initEE(std::move(Owner_12));
    ExecutionEngine* EE13 = initEE(std::move(Owner_13));
    ExecutionEngine* EE14 = initEE(std::move(Owner_14));
    ExecutionEngine* EE15 = initEE(std::move(Owner_15));
    ExecutionEngine* EE16 = initEE(std::move(Owner_16));
    uint64_t func_addr_1 = EE1->getFunctionAddress("rules");
    uint64_t func_addr_2 = EE2->getFunctionAddress("rules");
    uint64_t func_addr_3 = EE3->getFunctionAddress("rules");
    uint64_t func_addr_4 = EE4->getFunctionAddress("rules");
    uint64_t func_addr_5 = EE5->getFunctionAddress("rules");
    uint64_t func_addr_6 = EE6->getFunctionAddress("rules");
    uint64_t func_addr_7 = EE7->getFunctionAddress("rules");
    uint64_t func_addr_8 = EE8->getFunctionAddress("rules");
    uint64_t func_addr_9 = EE9->getFunctionAddress("rules");
    uint64_t func_addr_10 = EE10->getFunctionAddress("rules");
    uint64_t func_addr_11 = EE11->getFunctionAddress("rules");
    uint64_t func_addr_12 = EE12->getFunctionAddress("rules");
    uint64_t func_addr_13 = EE13->getFunctionAddress("rules");
    uint64_t func_addr_14 = EE14->getFunctionAddress("rules");
    uint64_t func_addr_15 = EE15->getFunctionAddress("rules");
    uint64_t func_addr_16 = EE16->getFunctionAddress("rules");
    if (func_addr_1 == 0 || func_addr_2 == 0 || func_addr_3 == 0 || func_addr_4 == 0 || func_addr_5 == 0 || 
        func_addr_6 == 0 || func_addr_7 == 0 || func_addr_8 == 0 || func_addr_9 == 0 || func_addr_10 == 0 ||
        func_addr_11 == 0 || func_addr_12 == 0 || func_addr_13 == 0 || func_addr_14 == 0|| 
        func_addr_15 == 0 || func_addr_16 == 0) {
        printf("Error, Cannot find function\n");
        return 0;
    }
    func_type func_1 = (func_type) func_addr_1;
    func_type func_2 = (func_type) func_addr_2;
    func_type func_3 = (func_type) func_addr_3;
    func_type func_4 = (func_type) func_addr_4;
    func_type func_5 = (func_type) func_addr_5;
    func_type func_6 = (func_type) func_addr_6;
    func_type func_7 = (func_type) func_addr_7;
    func_type func_8 = (func_type) func_addr_8;
    func_type func_9 = (func_type) func_addr_9;
    func_type func_10 = (func_type) func_addr_10;
    func_type func_11 = (func_type) func_addr_11;
    func_type func_12 = (func_type) func_addr_12;
    func_type func_13 = (func_type) func_addr_13;
    func_type func_14 = (func_type) func_addr_14;
    func_type func_15 = (func_type) func_addr_15;
    func_type func_16 = (func_type) func_addr_16;
    
    //cout << "Modules total size is " << sizeof(*M1)+sizeof(*M2)+sizeof(*M4)+sizeof(*M5)<< endl;
    
    ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    inputFile.clear();
	inputFile.open(argv[1]); // Open test file
	if (!inputFile) // Exit if test file is not found
	{
		cerr << "Error: Testing data file not found!" << endl;
		exit(-1);
	}
	while (getline(inputFile, singleInstance)) // Store test data in a table
	{
		parse(singleInstance, dataTable);
	}
    int row = dataTable.size()-1;
    int column = dataTable[0].size()-1;
    double dataArrayDouble[row][column];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabelsDouble;
    // Stores the given class labels in the test data in Int
    vd givenClassLabelsDouble;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
    {
        string data = dataTable[i][1];
        double dataDouble = mresult[data];
        givenClassLabelsDouble.push_back(dataDouble);
        for (int j = 0; j < dataTable[0].size()-1-2; j++){
            dataArrayDouble[i-1][j] = std::stod(dataTable[i][j+2]);
        }
    }
    double someDouble;
    double resultDouble1, resultDouble2, resultDouble3, resultDouble4, resultDouble5,
    resultDouble6, resultDouble7, resultDouble8, resultDouble9, resultDouble10,resultDouble11,
    resultDouble12, resultDouble13, resultDouble14, resultDouble15, resultDouble16;
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
    {
        someDouble = -1.0;
        resultDouble1 = func_1(dataArrayDouble[i]);
        if( resultDouble1 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble1);
            continue;
        }
        resultDouble2 = func_2(dataArrayDouble[i]);
        if( resultDouble2 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble2);
            continue;
        }
        resultDouble3 = func_3(dataArrayDouble[i]);
        if( resultDouble3 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble3);
            continue;
        }
        resultDouble4 = func_4(dataArrayDouble[i]);
        if( resultDouble4 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble4);
            continue;
        }
        resultDouble5 = func_5(dataArrayDouble[i]);
        if( resultDouble5 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble5);
            continue;
        }
        resultDouble6 = func_6(dataArrayDouble[i]);
        if( resultDouble6 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble6);
            continue;
        }
        resultDouble7 = func_7(dataArrayDouble[i]);
        if( resultDouble7 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble7);
            continue;
        }
        resultDouble8 = func_8(dataArrayDouble[i]);
        if( resultDouble8 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble8);
            continue;
        }
        resultDouble9 = func_9(dataArrayDouble[i]);
        if( resultDouble9 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble9);
            continue;
        }
        resultDouble10 = func_10(dataArrayDouble[i]);
        if( resultDouble10 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble10);
            continue;
        }
        resultDouble11 = func_11(dataArrayDouble[i]);
        if( resultDouble11 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble11);
            continue;
        }
        resultDouble12 = func_12(dataArrayDouble[i]);
        if( resultDouble12 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble12);
            continue;
        }
        resultDouble13 = func_13(dataArrayDouble[i]);
        if( resultDouble13 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble13);
            continue;
        }
        resultDouble14 = func_14(dataArrayDouble[i]);
        if( resultDouble14 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble14);
            continue;
        }
        resultDouble15 = func_15(dataArrayDouble[i]);
        if( resultDouble15 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble15);
            continue;
        }
        resultDouble16 = func_16(dataArrayDouble[i]);
        if( resultDouble16 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble16);
            continue;
        }
        if(resultDouble1 == -1.0 && resultDouble2 == -1.0 && resultDouble3 == -1.0 && resultDouble4 == -1.0 && resultDouble5 == -1.0 &&
            resultDouble6 == -1.0 && resultDouble7 == -1.0 && resultDouble8 == -1.0 && resultDouble9 == -1.0 && resultDouble10 == -1.0 &&
            resultDouble11 == -1.0 && resultDouble12 == -1.0 && resultDouble13 == -1.0 && resultDouble14 == -1.0 && resultDouble15 == -1.0 &&
            resultDouble16 == -1.0){
            predictedClassLabelsDouble.push_back(someDouble);
            continue;
        }
    }
    end=clock();
    cout<<"Time Using: "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    dataTable.clear();
    // Print output
    ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
    // Print predictions
	printPredictions(givenClassLabelsDouble, predictedClassLabelsDouble);
	return 0;
}