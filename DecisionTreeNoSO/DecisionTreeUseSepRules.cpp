#include "header.h"

int main(int argc, const char *argv[])
{
    clock_t start,end;
    msi mdata;
    msi mresult;
    mdata["Sunny"] = 1;
    mdata["Overcast"] = 2;
    mdata["Rain"] = 3;
    mdata["high"] = 4;
    mdata["normal"] = 5;
    mdata["strong"] = 6;
    mdata["weak"] = 7;
    mresult["yes"] = 1;
    mresult["no"] = 2;
    mresult["none"] = -1;
    char code_1[] = {
        0x55,
        0x48,0x89,0xe5,
        0x48,0x89,0x7d,0xf0,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x01,
        0x0f,0x85,0x1a,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x04,0x04,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x02,0x00,0x00,0x00,
        0xe9,0x07,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0x8b,0x45,0xfc,
        0x5d,
        0xc3
    };
    char code_2[] = {
        0x55,
        0x48,0x89,0xe5,
        0x48,0x89,0x7d,0xf0,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x01,
        0x0f,0x85,0x1a,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x04,0x05,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x01,0x00,0x00,0x00,
        0xe9,0x07,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0x8b,0x45,0xfc,
        0x5d,
        0xc3
    };
    char code_3[] = {
        0x55,
        0x48,0x89,0xe5,
        0x48,0x89,0x7d,0xf0,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x02,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x01,0x00,0x00,0x00,
        0xe9,0x07,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0x8b,0x45,0xfc,
        0x5d,
        0xc3
    };
    char code_4[] = {
        0x55,
        0x48,0x89,0xe5,
        0x48,0x89,0x7d,0xf0,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x03,
        0x0f,0x85,0x1a,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x08,0x06,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x02,0x00,0x00,0x00,
        0xe9,0x07,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0x8b,0x45,0xfc,
        0x5d,
        0xc3
    };
    char code_5[] = {
        0x55,
        0x48,0x89,0xe5,
        0x48,0x89,0x7d,0xf0,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x03,
        0x0f,0x85,0x1a,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x08,0x07,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x01,0x00,0x00,0x00,
        0xe9,0x07,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0x8b,0x45,0xfc,
        0x5d,
        0xc3
    };
    // Allocate a piece of memory to store machine code
    void * temp_1 = mmap(NULL, sizeof(code_1), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    void * temp_2 = mmap(NULL, sizeof(code_2), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    void * temp_3 = mmap(NULL, sizeof(code_3), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    void * temp_4 = mmap(NULL, sizeof(code_4), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    void * temp_5 = mmap(NULL, sizeof(code_5), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // Store machine code into memory
    memcpy(temp_1, code_1, sizeof(code_1));
    memcpy(temp_2, code_2, sizeof(code_2));
    memcpy(temp_3, code_3, sizeof(code_3));
    memcpy(temp_4, code_4, sizeof(code_4));
    memcpy(temp_5, code_5, sizeof(code_5));
    // Type conversion, converting memory to a function pointer
    rules_func_t p1_testDataOnDecisionTreeRules = (rules_func_t)temp_1;
    rules_func_t p2_testDataOnDecisionTreeRules = (rules_func_t)temp_2;
    rules_func_t p3_testDataOnDecisionTreeRules = (rules_func_t)temp_3;
    rules_func_t p4_testDataOnDecisionTreeRules = (rules_func_t)temp_4;
    rules_func_t p5_testDataOnDecisionTreeRules = (rules_func_t)temp_5;
	ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvi dataTableInt;// Input data in the form of a vector of vector of Ints
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
    int dataArrayInt[row][column];
    // Stores the predicted class labels for each row in Int
    vi predictedClassLabelsInt;
    // Stores the given class labels in the test data in Int
    vi givenClassLabelsInt;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
	{
        string data = dataTable[i][dataTable[0].size()-1];
        int dataInt = mresult[data];
        givenClassLabelsInt.push_back(dataInt);
        for (int j = 0; j < dataTable[0].size(); j++){
            dataArrayInt[i-1][j] = mdata[dataTable[i][j]];
        }
	}
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
	{
        int someInt = -1;
        int resultInt1, resultInt2, resultInt3, resultInt4, resultInt5;
        resultInt1 = p1_testDataOnDecisionTreeRules(dataArrayInt[i]);
        if( resultInt1 != -1){
            predictedClassLabelsInt.push_back(resultInt1);
            continue;
        }
        resultInt2 = p2_testDataOnDecisionTreeRules(dataArrayInt[i]);
        if( resultInt2 != -1){
            predictedClassLabelsInt.push_back(resultInt2);
            continue;
        }
        resultInt3 = p3_testDataOnDecisionTreeRules(dataArrayInt[i]);
        if( resultInt3 != -1){
            predictedClassLabelsInt.push_back(resultInt3);
            continue;
        }
        resultInt4 = p4_testDataOnDecisionTreeRules(dataArrayInt[i]);
        if( resultInt4 != -1){
            predictedClassLabelsInt.push_back(resultInt4);
            continue;
        }
        resultInt5 = p5_testDataOnDecisionTreeRules(dataArrayInt[i]);
        if( resultInt5 != -1){
            predictedClassLabelsInt.push_back(resultInt5);
            continue;
        }
        if(resultInt1 == -1 && resultInt2 == -1 && resultInt3 == -1 && resultInt4 == -1 && resultInt5 == -1){
            predictedClassLabelsInt.push_back(someInt);
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
	printPredictions(givenClassLabelsInt, predictedClassLabelsInt);
	return 0;
}