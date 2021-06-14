#include <string>
using namespace std;

extern "C" struct treenode {
    double data; //value to compare if not leaf, return value if leaf
    int index; //index to compare, -1 if leaf
    bool isLeaf; //leaf or not
    string comSymbol; //symbol to compare, "?" for leaf
    struct treenode *left; //pointer to left child
    struct treenode *right; //pointer to right child
};

extern "C" double testDataOnBinDecisionTree(double * dataTableElement, treenode* root)
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