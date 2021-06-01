extern "C" double testDataOnDecisionTreeRules(double * dataTableElement){
    if(dataTableElement[2]<=2.45){
        return 1.0;
    }else{
        if(dataTableElement[2]<=1.75){
            if(dataTableElement[2]<=4.95){
                if(dataTableElement[2]<=1.65){
                    return 2.0;
                }else{
                    return 3.0;
                }
            }else{
                if(dataTableElement[2]<=1.55){
                    return 3.0;
                }else{
                    if(dataTableElement[2]<=5.45){
                        return 2.0;
                    }else{
                        return 3.0;
                    }
                }
            }
        }else{
            if(dataTableElement[2]<=4.85){
                if(dataTableElement[0]<=5.95){
                    return 2.0;
                }else{
                    return 3.0;
                }
            }else{
                return 3.0;
            }
        }
    }
}