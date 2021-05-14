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
    mdata["Outlook"] = 8;
    mdata["Humidity"] = 9;
    mdata["Wind"] = 10;
    mdata["Result"] = 11;
    mresult["yes"] = 1;
    mresult["no"] = 2;
    mresult["none"] = -1;
	ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvi dataTableInt;// Input data in the form of a vector of vector of Ints
    vvs dataTableTest;// Input test data in the form of a vector of vector of strings
    vvi dataTableIntTest;// Input test data in the form of a vector of vector of Ints
	inputFile.open(argv[1]);
    // If input file does not exist, print error and exit
	if (!inputFile)
	{
		cerr << "Error: Training data file not found!" << endl;
		exit(-1);
	}
    
/* Decision tree training phase. In this phase, the training data is read from the file and stored into a vvs using the parse() function. The generateTableInfo() function extracts the attribute (column) names and also the values that each column can take. This information is also stored in a vvs. buildDecisionTree() function recursively builds trains the decision tree*/
    
    // Read from file, parse and store data
	while (getline(inputFile, singleInstance))
	{
		parse(singleInstance, dataTable);
	}
	inputFile.close();// Close input file
    // Transfer input data from string to Int using map
    for (int i = 0; i < dataTable.size(); i++)
	{
        if(i==0){
            vi dataTableIntRow;
            for(int j = 0; j < dataTable[0].size(); j++){
                dataTableIntRow.push_back(mdata[dataTable[i][j]]);
            }
            dataTableInt.push_back(dataTableIntRow);
            dataTableIntRow.clear();
        }else{
            vi dataTableIntRow;
            for (int j = 0; j < dataTable[0].size()-1; j++){
                dataTableIntRow.push_back(mdata[dataTable[i][j]]);
            }
            dataTableIntRow.push_back(mresult[dataTable[i][dataTable[0].size()-1]]);
            dataTableInt.push_back(dataTableIntRow);
            dataTableIntRow.clear();
        }
	}
    // Stores all the attributes and their values in a vector of vector of strings named tableInfo
	vvi tableInfo = generateTableInfo(dataTableInt);
    // Declare and assign memory for the root node of the Decision Tree
	node* root = new node;
    // Recursively build and train decision tree
	root = buildDecisionTree(dataTableInt, root, tableInfo);
    // printDecisionTree(root);
	dataTable.clear(); // clear dataTable of training data to store testing data
    
/* Decision tree testing phase. In this phase, the testing is read from the file, parsed and stored. Each row in the table is made to traverse down the decision tree till a class label is found*/
    
	inputFile.clear();
	inputFile.open(argv[2]);// Open test file
	if (!inputFile)// Exit if test file is not found
	{
		cerr << "Error: Testing data file not found!" << endl;
		exit(-1);
	}
    // Store test data in a table
	while (getline(inputFile, singleInstance))
	{
		parse(singleInstance, dataTableTest);
	}
	inputFile.close();// Close input file
    // Transfer input data from string to Int using map
    for (int i = 0; i < dataTableTest.size(); i++)
	{
        if(i==0){
            vi dataTableIntTestRow;
            for(int j = 0; j < dataTableTest[0].size(); j++){
                dataTableIntTestRow.push_back(mdata[dataTableTest[i][j]]);
            }
            dataTableIntTest.push_back(dataTableIntTestRow);
            dataTableIntTestRow.clear();
        }else{
            vi dataTableIntTestRow;
            for (int j = 0; j < dataTableTest[0].size()-1; j++){
                dataTableIntTestRow.push_back(mdata[dataTableTest[i][j]]);
            }
            dataTableIntTestRow.push_back(mresult[dataTableTest[i][dataTableTest[0].size()-1]]);
            dataTableIntTest.push_back(dataTableIntTestRow);
            dataTableIntTestRow.clear();
        }
	}
    // Stores the predicted class labels for each row in Int
    vi predictedClassLabelsInt;
    // Stores the given class labels in the test data in Int
    vi givenClassLabelsInt;
    // Store given class labels in vector of strings named givenClassLabels
	for (int i = 1; i < dataTableTest.size(); i++)
	{
        string data = dataTableTest[i][dataTableTest[0].size()-1];
        int dataIntTest = mresult[data];
        givenClassLabelsInt.push_back(dataIntTest);
	}
    start=clock();
    // Predict class labels based on the decision tree
	for (int i = 1; i < dataTableIntTest.size(); i++)
	{
		int someIntTest = testDataOnDecisionTree(dataTableIntTest[i],root,tableInfo);
		predictedClassLabelsInt.push_back(someIntTest);
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