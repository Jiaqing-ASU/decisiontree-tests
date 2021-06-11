#include "header.h"

double testDataOnDecisionTreeRule1(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]<=16.54 && dataTableElement[13]<=37.61 && dataTableElement[21]<=33.27){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule2(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]<=16.54 && dataTableElement[13]<=37.61 && dataTableElement[21]>33.27 && dataTableElement[21]<=34.14){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule3(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]<=16.54 && dataTableElement[13]<=37.61 && dataTableElement[21]>33.27 && dataTableElement[21]>34.14){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule4(double* dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]<=16.54 && dataTableElement[13]>37.61 && dataTableElement[4]<=0.091){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule5(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]<=16.54 && dataTableElement[13]>37.61 && dataTableElement[4]>0.091 && dataTableElement[17]<=0.012){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule6(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]<=16.54 && dataTableElement[13]>37.61 && dataTableElement[4]>0.091 && dataTableElement[17]>0.012){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule7(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]>16.54 && dataTableElement[21]<=20.22){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule8(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]>16.54 && dataTableElement[21]>20.22 && dataTableElement[17]<=0.011){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule9(double * dataTableElement){
    if(dataTableElement[7]<=0.052 && dataTableElement[20]>16.54 && dataTableElement[21]>20.22 && dataTableElement[17]>0.011){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule10(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]<=0.225){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule11(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]>0.225 && dataTableElement[23]<=710.2 && dataTableElement[21]<=25.95){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule12(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]>0.225 && dataTableElement[23]<=710.2 && dataTableElement[21]>25.95 && dataTableElement[9]<=0.065){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule13(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]>0.225 && dataTableElement[23]<=710.2 && dataTableElement[21]>25.95 && dataTableElement[9]>0.065){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule14(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]>0.225 && dataTableElement[23]>710.2 && dataTableElement[1]<=14.12 && dataTableElement[25]<=0.361){
        return 1.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule15(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]>0.225 && dataTableElement[23]>710.2 && dataTableElement[1]<=14.12 && dataTableElement[25]>0.361){
        return 2.0;
    }else{
        return -1.0;
    }
}

double testDataOnDecisionTreeRule16(double * dataTableElement){
    if(dataTableElement[7]>0.052 && dataTableElement[26]>0.225 && dataTableElement[23]>710.2 && dataTableElement[1]>14.12){
        return 1.0;
    }else{
        return -1.0;
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
        for (int j = 2; j < dataTable[0].size()-1; j++){
            dataArrayDouble[i-1][j] = std::stod(dataTable[i][j]);
        }
	}
    double someDouble;
    double resultDouble1, resultDouble2, resultDouble3, resultDouble4, resultDouble5,
    resultDouble6, resultDouble7, resultDouble8, resultDouble9, resultDouble10,resultDouble11,
    resultDouble12, resultDouble13, resultDouble14, resultDouble15, resultDouble16;
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
	{
        someDouble = -1.0;
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
        resultDouble6 = testDataOnDecisionTreeRule6(dataArrayDouble[i]);
        if( resultDouble6 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble6);
            continue;
        }
        resultDouble7 = testDataOnDecisionTreeRule7(dataArrayDouble[i]);
        if( resultDouble7 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble7);
            continue;
        }
        resultDouble8 = testDataOnDecisionTreeRule8(dataArrayDouble[i]);
        if( resultDouble8 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble8);
            continue;
        }
        resultDouble9 = testDataOnDecisionTreeRule9(dataArrayDouble[i]);
        if( resultDouble9 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble9);
            continue;
        }
        resultDouble10 = testDataOnDecisionTreeRule10(dataArrayDouble[i]);
        if( resultDouble10 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble10);
            continue;
        }
        resultDouble11 = testDataOnDecisionTreeRule11(dataArrayDouble[i]);
        if( resultDouble11 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble11);
            continue;
        }
        resultDouble12 = testDataOnDecisionTreeRule12(dataArrayDouble[i]);
        if( resultDouble12 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble12);
            continue;
        }
        resultDouble13 = testDataOnDecisionTreeRule13(dataArrayDouble[i]);
        if( resultDouble13 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble13);
            continue;
        }
        resultDouble14 = testDataOnDecisionTreeRule14(dataArrayDouble[i]);
        if( resultDouble14 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble14);
            continue;
        }
        resultDouble15 = testDataOnDecisionTreeRule15(dataArrayDouble[i]);
        if( resultDouble15 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble15);
            continue;
        }
        resultDouble16 = testDataOnDecisionTreeRule16(dataArrayDouble[i]);
        if( resultDouble16 != -1.0){
            predictedClassLabelsDouble.push_back(resultDouble16);
            continue;
        }
        if(resultDouble1 == -1.0 && resultDouble2 == -1.0 && resultDouble3 == -1.0 && resultDouble4 == -1.0 && resultDouble5 == -1.0 &&
            resultDouble6 == -1.0 && resultDouble7 == -1.0 && resultDouble8 == -1.0 && resultDouble9 == -1.0 && resultDouble10 == -1.0 &&
            resultDouble11 == -1.0 && resultDouble12 == -1.0 && resultDouble13 == -1.0 && resultDouble14 == -1.0 && resultDouble15 == -1.0 &&
            resultDouble16 == -1.0){
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