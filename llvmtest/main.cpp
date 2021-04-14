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
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
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

ExecutionEngine* EE = NULL;
RTDyldMemoryManager* RTDyldMM = NULL;
typedef int32_t (*func_type)(int32_t*);

void initEE(std::unique_ptr<Module> Owner) {
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
}

int main()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    int givenArray[3] = {5,5,5};
    LLVMContext context;
    SMDiagnostic error;
    unique_ptr<Module> Owner = parseIRFile("test.bc", error, context);
    if(Owner == nullptr) {
        cout << "Load Bitcode File Error\n" << endl;
        return 0;
    }
    Module *M = Owner.get();
    outs() << "We just loaded a module:\n" << *M;
    initEE(std::move(Owner));
    uint64_t func_addr = EE->getFunctionAddress("rules");
    if (func_addr == 0) {
        printf("Error, Cannot find function\n");
        return 0;
    }
    func_type func = (func_type) func_addr;
    int result = func(givenArray);
    outs() << "Function Running Result: " << result << "\n";
    return 0;
}