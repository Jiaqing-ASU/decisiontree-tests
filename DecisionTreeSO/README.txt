function.cpp contains the functions which will be used in DecisionTree.cpp and DecisionTreeUseRules.cpp.

train.txt is a training dataset for building Decision Tree.

test.txt is a test dataset which is the same as train.txt.

smalltest.txt is a small test dataset which contains 300 instances.

largertest.txt is a larger test dataset which contains 3000 instances.

rules.cpp is a C source file which contains the rules.

librules.so is a .so library file which contains the rules.

add.cpp, libadd_c.so and test.cpp is a simple test used to test how to use .so file in a .cpp file.

To run the decision tree rules code:
$g++ -shared -fpic -lm -ldl -o librules.so rules.cpp
$g++ functions.cpp DecisionTreeUseRulesSO.cpp -ldl -o dtree
$./dtree test.txt