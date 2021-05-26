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

struct treenode* createNode(double data, int index, bool isLeaf, string comSymbol) {
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

void preorder(struct treenode *root) {
    if (root != NULL) {
    	cout << root->data << "\t";
    	cout << root->index << "\t";
    	cout << root->isLeaf << "\t";
    	cout << root->comSymbol << "\n";
        preorder(root->left);
        preorder(root->right);
    }
    else
        return;
}

double testDataOnBinDecisionTree(double * dataTableElement, treenode* root)
{
	while(root->isLeaf == 0){
		double inputValue = dataTableElement[root->index];
		if(inputValue == root->data){
			root = root->left;
		}else{
			root = root->right;
		}
	}
	return root->data;
}

int main(int argc, const char *argv[])
{
	//cout << "1" << endl;

    struct treenode *root= createNode(1.0,0,false,"=");
    //cout << "2" << endl;

    root->left= createNode(4.0,1,false,"=");
    root->right= createNode(2.0,0,false,"=");
    //cout << "3" << endl;

    root->left->left= createNode(2.0,-1,true,"?");
    root->left->right= createNode(5.0,1,false,"=");
    root->right->left= createNode(1.0,-1,true,"?");
    root->right->right= createNode(3.0,0,false,"=");
    //cout << "4" << endl;

    root->left->right->left= createNode(1.0,-1,true,"?");
    root->left->right->right= createNode(-1.0,-1,true,"?");
    root->right->right->left = createNode(6.0,2,false,"=");
    root->right->right->right = createNode(-1.0,-1,true,"?");
    //cout << "5" << endl;

    root->right->right->left->left = createNode(2.0,-1,true,"?");
    root->right->right->left->right = createNode(7.0,2,false,"=");
    //cout << "6" << endl;

    root->right->right->left->right->left = createNode(1.0,-1,true,"?");
    root->right->right->left->right->right = createNode(-1.0,-1,true,"?");
    //cout << "7" << endl;

    //printf("PRE-ORDER: \n");
    //preorder(root);

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
        double someDouble = testDataOnBinDecisionTree(dataArrayDouble[i],root);
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