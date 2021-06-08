#include <string>
using namespace std;

extern "C" struct Treenode {
    int index; //index to compare, -1 if leaf
    double data; //value to compare if not leaf, return value if leaf
    bool isLeaf; //leaf or not
    int left; //left child index in tree array
    int right; //right child index in tree array
    string comSymbol; //symbol to compare, "?" for leaf
};

extern "C" double testDataOnBinDecisionTree(double * dataTableElement, Treenode* treenodes)
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