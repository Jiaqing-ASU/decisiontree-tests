#include "header.h"

string testDataOnDecisionTreeRules(vector<string>& dataTableElement){
    if(dataTableElement[0]=="Sunny"){
        if(dataTableElement[1]=="high"){
            return "no";
        }else{
            return "yes";
        }
    }else if(dataTableElement[0]=="Overcast"){
        return "yes";
    }else{
        if(dataTableElement[2]=="strong"){
            return "no";
        }else{
            return "yes";
        }
    }
}

int main(int argc, const char *argv[])
{
    clock_t start,end;
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
		string someString = testDataOnDecisionTreeRules(dataTable[i]);
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