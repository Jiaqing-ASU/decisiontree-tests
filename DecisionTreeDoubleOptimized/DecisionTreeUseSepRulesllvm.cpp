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
    msd mdata;
    msd mresult;
    mdata["Sunny"] = 1.0;
    mdata["Overcast"] = 2.0;
    mdata["Rain"] = 3.0;
    mdata["high"] = 4.0;
    mdata["normal"] = 5.0;
    mdata["strong"] = 6.0;
    mdata["weak"] = 7.0;
    mresult["yes"] = 1.0;
    mresult["no"] = 2.0;
    mresult["none"] = -1.0;
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    LLVMContext context;
    SMDiagnostic error;
    unique_ptr<Module> Owner_1 = parseIRFile("rule1.bc", error, context);
    unique_ptr<Module> Owner_2 = parseIRFile("rule2.bc", error, context);
    //unique_ptr<Module> Owner_3 = parseIRFile("rule3.bc", error, context);
    unique_ptr<Module> Owner_4 = parseIRFile("rule4.bc", error, context);
    unique_ptr<Module> Owner_5 = parseIRFile("rule5.bc", error, context);
    if(Owner_1 == nullptr || Owner_2 == nullptr || Owner_4 == nullptr || Owner_5 == nullptr) {
        cout << "Load Bitcode Files Error\n" << endl;
        return 0;
    }
    Module *M1 = Owner_1.get();
    Module *M2 = Owner_2.get();
    //Module *M3 = Owner_3.get();
    Module *M4 = Owner_4.get();
    Module *M5 = Owner_5.get();
    ExecutionEngine* EE1 = initEE(std::move(Owner_1));
    ExecutionEngine* EE2 = initEE(std::move(Owner_2));
    //ExecutionEngine* EE3 = initEE(std::move(Owner_3));
    ExecutionEngine* EE4 = initEE(std::move(Owner_4));
    ExecutionEngine* EE5 = initEE(std::move(Owner_5));
    uint64_t func_addr_1 = EE1->getFunctionAddress("rules");
    uint64_t func_addr_2 = EE2->getFunctionAddress("rules");
    //uint64_t func_addr_3 = EE3->getFunctionAddress("rules");
    uint64_t func_addr_4 = EE4->getFunctionAddress("rules");
    uint64_t func_addr_5 = EE5->getFunctionAddress("rules");
    if (func_addr_1 == 0 || func_addr_2 == 0 || func_addr_4 == 0 || func_addr_5 == 0) {
        printf("Error, Cannot find function\n");
        return 0;
    }
    func_type func_1 = (func_type) func_addr_1;
    func_type func_2 = (func_type) func_addr_2;
    //func_type func_3 = (func_type) func_addr_3;
    func_type func_4 = (func_type) func_addr_4;
    func_type func_5 = (func_type) func_addr_5;
    
    //cout << "Modules total size is " << sizeof(*M1)+sizeof(*M2)+sizeof(*M4)+sizeof(*M5)<< endl;
    //cout << "Functions total size is " << sizeof(func_1)+sizeof(func_2)+sizeof(func_3)+sizeof(func_4)+sizeof(func_5)<< endl;
    
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
    int column = dataTable[0].size();
    double dataArrayDouble[row][column];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabelsDouble;
    // Stores the given class labels in the test data in Int
    vd givenClassLabelsDouble;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
	{
        string data = dataTable[i][dataTable[0].size()-1];
        double dataDouble = mresult[data];
        givenClassLabelsDouble.push_back(dataDouble);
        for (int j = 0; j < dataTable[0].size(); j++){
            dataArrayDouble[i-1][j] = mdata[dataTable[i][j]];
        }
	}
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
	{
        double someDouble = -1.0;
        double resultDouble1, resultDouble2, resultDouble3, resultDouble4, resultDouble5;
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
        /*resultDouble3 = func_3(dataArrayDouble[i]);
        if( resultDouble3 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble3);
            continue;
        }*/
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
        if(resultDouble1 == -1.0 && resultDouble2 == -1.0 && resultDouble4 == -1.0 && resultDouble5 == -1.0){
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