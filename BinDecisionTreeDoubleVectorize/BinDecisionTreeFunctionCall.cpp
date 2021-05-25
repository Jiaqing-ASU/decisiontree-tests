#include "header.h"

double* testDataOnDecisionTreeRules(double dataTableElement[30][3], int n, double* results){
    for(int i = 0; i < n; i++){
        if(dataTableElement[i][0]==1.0){
            if(dataTableElement[i][1]==4.0){
                results[i] = 2.0;
            }else{
                if(dataTableElement[i][1]==5.0){
                    results[i] = 1.0;
                }else{
                    results[i] = -1.0;
                }
            }
        }else{
            if(dataTableElement[i][0]==2.0){
                results[i] = 1.0;
            }else{
                if(dataTableElement[i][0]==3.0){
                    if(dataTableElement[i][2]==6.0){
                        results[i] = 2.0;
                    }else{
                        if(dataTableElement[i][2]==7.0){
                            results[i] = 1.0;
                        }else{
                            results[i] = -1.0;
                        }
                    }
                }else{
                    results[i] = -1.0;
                }
            }
        }
    }
    return results;
}

int main(int argc, const char *argv[])
{
    clock_t start,end;
    msi mattributes;
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
    mattributes["Outlook"] = 0;
    mattributes["Humidity"] = 1;
    mattributes["Wind"] = 2;
    mattributes["Result"] = 3;
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
    int column = dataTable[0].size();
    double dataArrayDouble[100][30][3];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabels;
    // Stores the given class labels in the test data in Int
    vd givenClassLabels;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for(int k = 0; k < row/30; k++){
        for (int i = k*30+1; i <= (k+1)*30; i++){
            string data = dataTable[i][dataTable[0].size()-1];
            double dataDouble = mresult[data];
            givenClassLabels.push_back(dataDouble);
            for (int j = 0; j < dataTable[0].size(); j++){
                dataArrayDouble[k][i-k*30-1][j] = mdata[dataTable[i][j]];
            }
        }
    }
    start=clock();
    // Predict class labels based on the decision tree rule function
    for (int i = 0; i < row/30; i++)
    {
        double someDouble[30];
        double* valuePtr = testDataOnDecisionTreeRules(dataArrayDouble[i],30, someDouble);
        for(int j = 0; j < 30; j++){
            predictedClassLabels.push_back(valuePtr[j]);
        }
    }
    end=clock();
    cout << "Time Using: " <<(double)(end-start)/CLOCKS_PER_SEC << endl;
	dataTable.clear();
    // Print output
	ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
	// Print predictions
    printPredictions(givenClassLabels, predictedClassLabels);
	return 0;
}