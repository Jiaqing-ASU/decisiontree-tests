extern "C" double testDataOnDecisionTreeRules(double * dataTableElement){
    if(dataTableElement[0]==1.0){
        if(dataTableElement[1]==4.0){
            return 2.0;
        }else{
            if(dataTableElement[1]==5.0){
                return 1.0;
            }else{
                return -1.0;
            }
        }
    }else{
        if(dataTableElement[0]==2.0){
            return 1.0;
        }else{
            if(dataTableElement[0]==3.0){
                if(dataTableElement[2]==6.0){
                    return 2.0;
                }else{
                    if(dataTableElement[2]==7.0){
                        return 1.0;
                    }else{
                        return -1.0;
                    }
                }
            }else{
                return -1.0;
            }
        }
    }
}