#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <math.h>
#include <float.h>
#include <cstdlib>
#include <iomanip>
#include<time.h>

using namespace std;

typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<int> vi;
typedef map<string, int> msi;
typedef vector<double> vd;

// struct node defines the structure of a node of the decision tree
struct node
{
	string splitOn;// Stores which attribute to split on at a particular node
	string label;// Stores the class label for leaf nodes.
    /*For nodes that are not leaf nodes, it stores the value of the attribute of the parent's' split*/
	bool isLeaf;// boolean flag for leaf nodes
	vector<string> childrenValues;// Store the values of the childrens' attributes
	vector<node*> children;// Store pointers to the children of a node
};

void parse(string&, vvs&);// Parse a single line from the input file and stores the information into a vector of vector of strings
vvs pruneTable(vvs&, string&, string);// Prune a table based on a column/attribute's name and the value of that attribute. Removes that column and all instances that have that value for that column
node* buildDecisionTree(vvs&, node*, vvs&);// Build the decision tree based on the table it is passed
bool isHomogeneous(vvs&);// Return true if all instances in a subtable at a node have the same class label
vi countDistinct(vvs&, int);// Return a vector of integers containing the counts of all the various values of an attribute/column
string decideSplittingColumn(vvs&);// Return the column on which to split on. Decision of column is based on entropy
int returnColumnIndex(string&, vvs&);// Return the index of a column in a subtable
bool tableIsEmpty(vvs&);// Return true if a subtable is empty
string testDataOnDecisionTree(vs&, node*, vvs&);// Run a single instance of the test data through the decision tree and return the predicted class label
int returnIndexOfVector(vs&, string);// Return the index of a string in a vector of strings
void printPredictions(vs&, vs&);// Output the predictions to file
vvs generateTableInfo(vvs &dataTable);// Generate information about the table in a vector of vector of stings