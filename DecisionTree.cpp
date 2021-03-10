#include "header.h"

int main(int argc, const char *argv[])
{
    clock_t start,end;
	ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
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
    // Stores all the attributes and their values in a vector of vector of strings named tableInfo
	vvs tableInfo = generateTableInfo(dataTable);
    // Declare and assign memory for the root node of the Decision Tree
	node* root = new node;
    // Recursively build and train decision tree
	root = buildDecisionTree(dataTable, root, tableInfo);
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
		parse(singleInstance, dataTable);
	}
	vs predictedClassLabels;// Stores the predicted class labels for each row
	vs givenClassLabels;// Stores the given class labels in the test data
    // Store given class labels in vector of strings named givenClassLabels
	for (int i = 1; i < dataTable.size(); i++)
	{
		string data = dataTable[i][dataTable[0].size()-1];
		givenClassLabels.push_back(data);
	}
    start=clock();
    // Predict class labels based on the decision tree
	for (int i = 1; i < dataTable.size(); i++)
	{
		string someString = testDataOnDecisionTree(dataTable[i], root, tableInfo);
		predictedClassLabels.push_back(someString);
	}
    end=clock();
    cout<<"Time Using: "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
	dataTable.clear();
    // Print output
	ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
	// Print predictions
    printPredictions(givenClassLabels, predictedClassLabels);
	return 0;
}