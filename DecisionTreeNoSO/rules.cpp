int testDataOnDecisionTreeRules(int * dataTableElement){
    if(dataTableElement[0]==1){
        if(dataTableElement[1]==4){
            return 2;
        }else if(dataTableElement[1]==5){
            return 1;
        }else{
            return -1;
        }
    }else if(dataTableElement[0]==2){
        return 1;
    }else if(dataTableElement[0]==3){
        if(dataTableElement[2]==6){
            return 2;
        }else if(dataTableElement[2]==7){
            return 1;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}