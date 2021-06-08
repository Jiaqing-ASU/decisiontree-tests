#include<stdio.h>
#include<malloc.h>
#include <string>
#include <iostream>
#include "header.h"
using namespace std;

struct Treenode {
    int index; //index to compare, -1 if leaf
    double data; //value to compare if not leaf, return value if leaf
    bool isLeaf; //leaf or not
    int left; //left child index in tree array
    int right; //right child index in tree array
    string comSymbol; //symbol to compare, "?" for leaf
};

double testDataOnBinDecisionTree(double * dataTableElement, Treenode* treenodes)
{
    int i = 0;
    while(treenodes[i].isLeaf == 0){
        double inputValue = dataTableElement[treenodes[i].index];
        if(treenodes[i].comSymbol == "="){
            if(inputValue == treenodes[i].data){
                i = treenodes[i].left;
            }else{
                i = treenodes[i].right;
            }
        }else if(treenodes[i].comSymbol == "<"){
            if(inputValue < treenodes[i].data){
                i = treenodes[i].left;
            }else{
                i = treenodes[i].right;
            }
        }else if(treenodes[i].comSymbol == ">"){
            if(inputValue > treenodes[i].data){
                i = treenodes[i].left;
            }else{
                i = treenodes[i].right;
            }
        }else if(treenodes[i].comSymbol == "<="){
            if(inputValue <= treenodes[i].data){
                i = treenodes[i].left;
            }else{
                i = treenodes[i].right;
            }
        }else if(treenodes[i].comSymbol == ">="){
            if(inputValue >= treenodes[i].data){
                i = treenodes[i].left;
            }else{
                i = treenodes[i].right;
            }
        }else if(treenodes[i].comSymbol == "!="){
            if(inputValue != treenodes[i].data){
                i = treenodes[i].left;
            }else{
                i = treenodes[i].right;
            }
        }
    }
    return treenodes[i].data;
}

int main(int argc, const char *argv[])
{
    Treenode treenodes[15];
    treenodes[0] = {0,1.0,false,1,2,"="};
    treenodes[1] = {1,4.0,false,3,4,"="};
    treenodes[2] = {0,2.0,false,5,6,"="};
    treenodes[3] = {-1,2.0,true,-1,-1,"?"};
    treenodes[4] = {1,5.0,false,7,8,"="};
    treenodes[5] = {-1,1.0,true,-1,-1,"?"};
    treenodes[6] = {0,3.0,false,9,10,"="};
    treenodes[7] = {-1,1.0,true,-1,-1,"?"};
    treenodes[8] = {-1,-1.0,true,-1,-1,"?"};
    treenodes[9] = {2,6.0,false,11,12,"="};
    treenodes[10] = {-1,-1.0,true,-1,-1,"?"};
    treenodes[11] = {-1,2.0,true,-1,-1,"?"};
    treenodes[12] = {2,7.0,false,13,14,"="};
    treenodes[13] = {-1,1.0,true,-1,-1,"?"};
    treenodes[14] = {-1,-1.0,true,-1,-1,"?"};

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
    double dataArrayDouble[row][column];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabels;
    // Stores the given class labels in the test data in Int
    vd givenClassLabels;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
    {
        string data = dataTable[i][dataTable[0].size()-1];
        double dataDouble = mresult[data];
        givenClassLabels.push_back(dataDouble);
        for (int j = 0; j < dataTable[0].size(); j++){
            dataArrayDouble[i-1][j] = mdata[dataTable[i][j]];
        }
    }
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
    {
        double someDouble = testDataOnBinDecisionTree(dataArrayDouble[i],treenodes);
        predictedClassLabels.push_back(someDouble);
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