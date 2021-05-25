extern "C" double* testDataOnDecisionTreeRules(double dataTableElement[30][3], int n, double* results){
    for(int i = 0; i < n; i++){
        if(dataTableElement[i][0]==1.0){
            if(dataTableElement[i][1]==4.0){
                results[i] = 2.0;
            }else{
                if(dataTableElement[i][1]==5.0){
                    results[i] = 1.0;
                }else{
                    results[i] = -1.0;
                }
            }
        }else{
            if(dataTableElement[i][0]==2.0){
                results[i] = 1.0;
            }else{
                if(dataTableElement[i][0]==3.0){
                    if(dataTableElement[i][2]==6.0){
                        results[i] = 2.0;
                    }else{
                        if(dataTableElement[i][2]==7.0){
                            results[i] = 1.0;
                        }else{
                            results[i] = -1.0;
                        }
                    }
                }else{
                    results[i] = -1.0;
                }
            }
        }
    }
    return results;
}