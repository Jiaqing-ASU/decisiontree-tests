#include "header.h"

double testDataOnDecisionTreeRules(double * dataTableElement){
    if(dataTableElement[7]<=0.052){
        if(dataTableElement[20]<=16.54){
            if(dataTableElement[13]<=37.61){
                if(dataTableElement[21]<=33.27){
                    return 2.0;
                }else{
                    if(dataTableElement[21]<=34.14){
                        return 1.0;
                    }else{
                        return 2.0;
                    }
                }
            }else{
                if(dataTableElement[4]<=0.091){
                    return 2.0;
                }else{
                    if(dataTableElement[17]<=0.012){
                        return 2.0;
                    }else{
                        return 1.0;
                    }
                }
            }
        }else{
            if(dataTableElement[21]<=20.22){
                return 2.0;
            }else{
                if(dataTableElement[17]<=0.011){
                    return 1.0;
                }else{
                    return 2.0;
                }
            }
        }
    }else{
        if(dataTableElement[26]<=0.225){
            return 2.0;
        }else{
            if(dataTableElement[23]<=710.2){
                if(dataTableElement[21]<=25.95){
                    return 2.0;
                }else{
                    if(dataTableElement[9]<=0.065){
                        return 2.0;
                    }else{
                        return 1.0;
                    }
                }
            }else{
                if(dataTableElement[1]<=14.12){
                    if(dataTableElement[25]<=0.361){
                        return 1.0;
                    }else{
                        return 2.0;
                    }
                }else{
                    return 1.0;
                }
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    clock_t start,end;
    msd mresult;
    mresult["B"] = 1.0;
    mresult["M"] = 2.0;
    ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvd dataTableDouble;// Input data in the form of a vector of vector of Doubles
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
    int column = dataTable[0].size()-1;
    double dataArrayDouble[row][column];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabelsDouble;
    // Stores the given class labels in the test data in Int
    vd givenClassLabelsDouble;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
    {
        string data = dataTable[i][1];
        double dataDouble = mresult[data];
        givenClassLabelsDouble.push_back(dataDouble);
        for (int j = 0; j < dataTable[0].size()-1-2; j++){
            dataArrayDouble[i-1][j] = std::stod(dataTable[i][j+2]);
        }
    }
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
	{
        double someDouble = testDataOnDecisionTreeRules(dataArrayDouble[i]);
		predictedClassLabelsDouble.push_back(someDouble);
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