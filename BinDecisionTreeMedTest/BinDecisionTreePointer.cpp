#include<stdio.h>
#include<malloc.h>
#include <string>
#include <iostream>
#include "header.h"
using namespace std;

struct treenode {
    double data; //value to compare if not leaf, return value if leaf
    int index; //index to compare, -1 if leaf
    bool isLeaf; //leaf or not
    string comSymbol; //symbol to compare, "?" for leaf
    struct treenode *left; //pointer to left child
    struct treenode *right; //pointer to right child
};

struct treenode* createNode(int index, double data, bool isLeaf, string comSymbol) {
    // this function will return the pointer for the new node
    struct treenode *newNode= (struct treenode *)malloc(sizeof(struct treenode));
    newNode->data = data;
    newNode->index = index;
    newNode->isLeaf = isLeaf;
    newNode->comSymbol = comSymbol;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

double testDataOnBinDecisionTree(double * dataTableElement, treenode* root)
{
	while(root->isLeaf == 0){
		double inputValue = dataTableElement[root->index];
		if(inputValue <= root->data){
			root = root->left;
		}else{
			root = root->right;
		}
	}
	return root->data;
}

int main(int argc, const char *argv[])
{
    struct treenode *root = createNode(7,0.052,false,"<=");

    root->left = createNode(20,16.54,false,"<=");
    root->right = createNode(26,0.225,false,"<=");

    root->left->left = createNode(13,37.61,false,"<=");
    root->left->right = createNode(21,20.22,false,"<=");

    root->right->left = createNode(-1,2.0,true,"?");
    root->right->right = createNode(23,710.2,false,"<=");

    root->left->left->left = createNode(21,33.27,false,"<=");
    root->left->left->right = createNode(4,0.091,false,"<=");

    root->left->right->left = createNode(-1,2.0,true,"?");
    root->left->right->right = createNode(17,0.011,false,"<=");

    root->right->right->left = createNode(21,25.95,false,"<=");
    root->right->right->right = createNode(1,14.12,false,"<=");

    root->left->left->left->left = createNode(-1,2.0,true,"?");
    root->left->left->left->right = createNode(21,34.14,false,"<=");

    root->left->left->right->left = createNode(-1,2.0,true,"?");
    root->left->left->right->right = createNode(17,0.012,false,"<=");

    root->left->right->right->left = createNode(-1,1.0,true,"?");
    root->left->right->right->right = createNode(-1,2.0,true,"?");

    root->right->right->left->left = createNode(-1,2.0,true,"?");
    root->right->right->left->right = createNode(9,0.065,false,"<=");

    root->right->right->right->left = createNode(25,0.361,false,"<=");
    root->right->right->right->right = createNode(-1,1.0,true,"?");

    root->left->left->left->right->left = createNode(-1,1.0,true,"?");
    root->left->left->left->right->right = createNode(-1,2.0,true,"?");

    root->left->left->right->right->left = createNode(-1,2.0,true,"?");
    root->left->left->right->right->right = createNode(-1,1.0,true,"?");

    root->right->right->left->right->left = createNode(-1,2.0,true,"?");
    root->right->right->left->right->right = createNode(-1,1.0,true,"?");

    root->right->right->right->left->left = createNode(-1,1.0,true,"?");
    root->right->right->right->left->right = createNode(-1,2.0,true,"?");

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
        double someDouble = testDataOnBinDecisionTree(dataArrayDouble[i],root);
        predictedClassLabelsDouble.push_back(someDouble);
    }
    end=clock();
    cout << "Time Using: " <<(double)(end-start)/CLOCKS_PER_SEC << endl;
	dataTable.clear();
    // Print output
	ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
	// Print predictions
    printPredictions(givenClassLabelsDouble, predictedClassLabelsDouble);
	return 0;
}