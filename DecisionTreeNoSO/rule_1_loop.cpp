int* testDataOnDecisionTreeRules(int ** dataTableElement, int n){
	int results[n];
    for(int i = 0; i < n; i++){
        if(dataTableElement[i][0]==1 && dataTableElement[i][1]==4){
        	results[i] = 2;
        }else{
        	results[i] = -1;
        }
    }
    return results;
}