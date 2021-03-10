#include <string>
#include <vector>
using namespace std;

string testDataOnDecisionTreeRules(vector<string> dataTableElement){
    if(dataTableElement[0]=="Sunny"){
        if(dataTableElement[1]=="high"){
            return "no";
        }else{
            return "yes";
        }
    }else if(dataTableElement[0]=="Overcast"){
        return "yes";
    }else{
        if(dataTableElement[2]=="strong"){
            return "no";
        }else{
            return "yes";
        }
    }
}