#include "header.h"

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
    mdata["Outlook"] = 8.0;
    mdata["Humidity"] = 9.0;
    mdata["Wind"] = 10.0;
    mdata["Result"] = 11.0;
    mresult["yes"] = 1.0;
    mresult["no"] = 2.0;
    mresult["none"] = -1.0;
	ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvd dataTableDouble;// Input data in the form of a vector of vector of Ints
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
            vd dataTableDoubleRow;
            for(int j = 0; j < dataTable[0].size(); j++){
                dataTableDoubleRow.push_back(mdata[dataTable[i][j]]);
            }
            dataTableDouble.push_back(dataTableDoubleRow);
            dataTableDoubleRow.clear();
        }else{
            vd dataTableDoubleRow;
            for (int j = 0; j < dataTable[0].size()-1; j++){
                dataTableDoubleRow.push_back(mdata[dataTable[i][j]]);
            }
            dataTableDoubleRow.push_back(mresult[dataTable[i][dataTable[0].size()-1]]);
            dataTableDouble.push_back(dataTableDoubleRow);
            dataTableDoubleRow.clear();
        }
	}
    // Stores all the attributes and their values in a vector of vector of strings named tableInfo
	vvd tableInfo = generateTableInfo(dataTableDouble);
    // Declare and assign memory for the root node of the Decision Tree
	node* root = new node;
    // Recursively build and train decision tree
	root = buildDecisionTree(dataTableDouble, root, tableInfo);
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
		parse(singleInstance, dataTable);
	}
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabels;
    // Stores the given class labels in the test data in Int
    vd givenClassLabels;
    // Store given class labels in vector of strings named givenClassLabels
	for (int i = 1; i < dataTable.size(); i++)
	{
        string data = dataTable[i][dataTable[0].size()-1];
        double dataDouble = mresult[data];
        givenClassLabels.push_back(dataDouble);
	}
    start=clock();
    // Predict class labels based on the decision tree
	for (int i = 1; i < dataTableDouble.size(); i++)
	{
		double someDouble = testDataOnDecisionTree(dataTableDouble[i],root,tableInfo);
		predictedClassLabels.push_back(someDouble);
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