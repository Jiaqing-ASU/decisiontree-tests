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
    char code[] = {
        0x55,
        0x48,0x89,0xe5,
        0x8b,0x07,
        0x83,0xf8,0x03,
        0x74,0x26,
        0x83,0xf8,0x02,
        0x74,0x3d,
        0x83,0xf8,0x01,
        0x75,0x3f,
        0x8b,0x47,0x04,
        0x31,0xc9,
        0x83,0xf8,0x05,
        0x0f,0x94,0xc1,
        0x8d,0x4c,0x09,0xff,
        0x83,0xf8,0x04,
        0xb8,0x02,0x00,0x00,0x00,
        0x0f,0x45,0xc1,
        0x5d,
        0xc3,
        0x8b,0x47,0x08,
        0x31,0xc9,
        0x83,0xf8,0x07,
        0x0f,0x94,0xc1,
        0x8d,0x4c,0x09,0xff,
        0x83,0xf8,0x06,
        0xb8,0x02,0x00,0x00,0x00,
        0x0f,0x45,0xc1,
        0x5d,
        0xc3,
        0xb8,0x01,0x00,0x00,0x00,
        0x5d,
        0xc3,
        0xb8,0xff,0xff,0xff,0xff,
        0x5d,
        0xc3
    };
    // Allocate a piece of memory to store machine code
    void * temp = mmap(NULL, sizeof(code), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    cout << "Char array size is " << sizeof(code) << endl;
    // Store machine code into memory
    memcpy(temp, code, sizeof(code));
    // Type conversion, converting memory to a function pointer
    rules_func_t p_testDataOnDecisionTreeRules = (rules_func_t)temp;
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
        int someInt = p_testDataOnDecisionTreeRules(dataArrayInt[i]);
		predictedClassLabelsInt.push_back(someInt);
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