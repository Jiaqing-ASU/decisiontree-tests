function.cpp contains the functions which will be used in DecisionTree.cpp and DecisionTreeUseRules.cpp and DecisionTreeUseSepRules.cpp.

train.txt is a training dataset for building Decision Tree.

test.txt is a test dataset which is the same as train.txt.

smalltest.txt is a small test dataset which contains 300 instances.

largertest.txt is a larger test dataset which contains 3000 instances.

rules.cpp is a C source file which contains the rules.

add.cpp and main.cpp is a simple test used to test how to use "objdump -j __text -d" to obtain machine code and how to use the machine code in a .cpp file.

To run the decision tree code. First go to Makefile and comment the "SOURCES....." line which you do not want to run and leave the one you want to run.

And then, use the following command if choosing to run tree nodes version:
$make clean
$make
$./dtree train.txt test.txt

Use the following command if choosing to run rules (including both one whole rule and separate rules) version:
$make clean
$make
$./dtree test.txt

To run the DecisionTreeUseSepRulesllvm.cpp, use the following command:
$clang++ -g DecisionTreeUseSepRulesllvm.cpp functions.cpp $(/usr/local/opt/llvm@11/bin/llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native orcjit) -rdynamic -O3 -o dtree
(Make sure to change the correct path of your llvm@11)

And then run the following command:
$./dtree test.txt