#include "header.h"

int testDataOnDecisionTreeRules(int * dataTableElement){
    if(dataTableElement[0]==1){
        if(dataTableElement[1]==4){
            return 2;
        }else if(dataTableElement[1]==5){
            return 1;
        }else{
            return -1;
        }
    }else if(dataTableElement[0]==2){
        return 1;
    }else if(dataTableElement[0]==3){
        if(dataTableElement[2]==6){
            return 2;
        }else if(dataTableElement[2]==7){
            return 1;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}

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
        0x48,0x89,0x7d,0xf0,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x01,
        0x0f,0x85,0x40,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x04,0x04,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x02,0x00,0x00,0x00,
        0xe9,0x93,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x04,0x05,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x01,0x00,0x00,0x00,
        0xe9,0x79,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0xe9,0x6d,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x02,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x01,0x00,0x00,0x00,
        0xe9,0x54,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x38,0x03,
        0x0f,0x85,0x40,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x08,0x06,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x02,0x00,0x00,0x00,
        0xe9,0x2d,0x00,0x00,0x00,
        0x48,0x8b,0x45,0xf0,
        0x83,0x78,0x08,0x07,
        0x0f,0x85,0x0c,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0x01,0x00,0x00,0x00,
        0xe9,0x13,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0xe9,0x07,0x00,0x00,0x00,
        0xc7,0x45,0xfc,0xff,0xff,0xff,0xff,
        0x8b,0x45,0xfc,
        0x5d,
        0xc3
    };
    // Allocate a piece of memory to store machine code
    void * temp = mmap(NULL, sizeof(code), PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // Store machine code into memory
    memcpy(temp, code, sizeof(code));
    // Type conversion, converting memory to a function pointer
    rules_func p_testDataOnDecisionTreeRules = (rules_func)temp;
	ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvi dataTableInt;
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
	vs predictedClassLabels;// Stores the predicted class labels for each row
    vi predictedClassLabelsInt;;// Stores the predicted class labels for each row in int
	vs givenClassLabels;// Stores the given class labels in the test data
    vi givenClassLabelsInt;// Stores the given class labels in the test data in int
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to int using map
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