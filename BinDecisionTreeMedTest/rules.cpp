extern "C" double testDataOnDecisionTreeRules(double * dataTableElement){
    if(dataTableElement[7]<=0.052){
        if(dataTableElement[20]<=16.54){
            if(dataTableElement[13]<=37.61){
                if(dataTableElement[21]<=33.27){
                    return 2.0;
                }else{
                    if(dataTableElement[21]<=34.14){
                        return 1.0;
                    }else{
                        return 2.0;
                    }
                }
            }else{
                if(dataTableElement[4]<=0.091){
                    return 2.0;
                }else{
                    if(dataTableElement[17]<=0.012){
                        return 2.0;
                    }else{
                        return 1.0;
                    }
                }
            }
        }else{
            if(dataTableElement[21]<=20.22){
                return 2.0;
            }else{
                if(dataTableElement[17]<=0.011){
                    return 1.0;
                }else{
                    return 2.0;
                }
            }
        }
    }else{
        if(dataTableElement[26]<=0.225){
            return 2.0;
        }else{
            if(dataTableElement[23]<=710.2){
                if(dataTableElement[21]<=25.95){
                    return 2.0;
                }else{
                    if(dataTableElement[9]<=0.065){
                        return 2.0;
                    }else{
                        return 1.0;
                    }
                }
            }else{
                if(dataTableElement[1]<=14.12){
                    if(dataTableElement[25]<=0.361){
                        return 1.0;
                    }else{
                        return 2.0;
                    }
                }else{
                    return 1.0;
                }
            }
        }
    }
}