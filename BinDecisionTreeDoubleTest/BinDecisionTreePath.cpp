#include "header.h"

double testDataOnDecisionTreeRule1(double * dataTableElement){
    if(dataTableElement[0]==1.0 && dataTableElement[1]==4.0){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule2(double * dataTableElement){
    if(dataTableElement[0]==1.0 && dataTableElement[1]==5.0){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule3(double * dataTableElement){
    if(dataTableElement[0]==2.0){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule4(double* dataTableElement){
    if(dataTableElement[0]==3.0 && dataTableElement[2]==6.0){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule5(double * dataTableElement){
    if(dataTableElement[0]==3.0 && dataTableElement[2]==7.0){
        return 1.0;
    }else{
        return -1.0;
    }
}

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
    mresult["yes"] = 1.0;
    mresult["no"] = 2.0;
    mresult["none"] = -1.0;

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
    int row = dataTable.size()-1;
    int column = dataTable[0].size();
    double dataArrayDouble[row][column];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabelsDouble;
    // Stores the given class labels in the test data in Int
    vd givenClassLabelsDouble;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
	{
        string data = dataTable[i][dataTable[0].size()-1];
        double dataDouble = mresult[data];
        givenClassLabelsDouble.push_back(dataDouble);
        for (int j = 0; j < dataTable[0].size(); j++){
            dataArrayDouble[i-1][j] = mdata[dataTable[i][j]];
        }
	}
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
	{
        double someDouble = -1.0;
        double resultDouble1, resultDouble2, resultDouble3, resultDouble4, resultDouble5;
        resultDouble1 = testDataOnDecisionTreeRule1(dataArrayDouble[i]);
        if( resultDouble1 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble1);
            continue;
        }
        resultDouble2 = testDataOnDecisionTreeRule2(dataArrayDouble[i]);
        if( resultDouble2 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble2);
            continue;
        }
        resultDouble3 = testDataOnDecisionTreeRule3(dataArrayDouble[i]);
        if( resultDouble3 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble3);
            continue;
        }
        resultDouble4 = testDataOnDecisionTreeRule4(dataArrayDouble[i]);
        if( resultDouble4 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble4);
            continue;
        }
        resultDouble5 = testDataOnDecisionTreeRule5(dataArrayDouble[i]);
        if( resultDouble5 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble5);
            continue;
        }
        if(resultDouble1 == -1.0 && resultDouble2 == -1.0 && resultDouble3 == -1.0 && resultDouble4 == -1.0 && resultDouble5 == -1.0){
            predictedClassLabelsDouble.push_back(someDouble);
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
	printPredictions(givenClassLabelsDouble, predictedClassLabelsDouble);
	return 0;
}