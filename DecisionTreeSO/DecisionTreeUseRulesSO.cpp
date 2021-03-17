#include "header.h"

int main(int argc, const char *argv[])
{
    clock_t start,end;
    msi mdata;
    msi mresult;
    mdata["Sunny"] = 1;
    mdata["Overcast"] = 2;
    mdata["Rain"] = 3;
    mdata["high"] = 4;
    mdata["normal"] = 5;
    mdata["strong"] = 6;
    mdata["weak"] = 7;
    mresult["yes"] = 1;
    mresult["no"] = 2;
    mresult["none"] = -1;
    ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvi dataTableInt;// Input data in the form of a vector of vector of Ints
    inputFile.clear();
	inputFile.open(argv[1]); // Open test file
	if (!inputFile) // Exit if test file is not found
	{
		cerr << "Error: Testing data file not found!" << endl;
		exit(-1);
	}
	while (getline(inputFile, singleInstance)) // Store test data in a table
	{
		parse(singleInstance, dataTable);
	}
    int row = dataTable.size()-1;
    int column = dataTable[0].size();
    int dataArrayInt[row][column];
    // Stores the predicted class labels for each row in Int
    vi predictedClassLabelsInt;
    // Stores the given class labels in the test data in Int
    vi givenClassLabelsInt;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
	{
        string data = dataTable[i][dataTable[0].size()-1];
        int dataInt = mresult[data];
        givenClassLabelsInt.push_back(dataInt);
        for (int j = 0; j < dataTable[0].size(); j++){
            dataArrayInt[i-1][j] = mdata[dataTable[i][j]];
        }
	}
    void* libHandle = dlopen("librules.so", RTLD_LAZY);
    if(!libHandle)
	{
		printf("open lib error\n");
		cout<<dlerror()<<endl;
		return -1;
	}
    typedef int (* rules_func_t)(int * a);
    rules_func_t rules_func= (rules_func_t)dlsym(libHandle, "testDataOnDecisionTreeRules");
    if(!rules_func)
	{
		cout<<dlerror()<<endl;
		dlclose(libHandle);
		return -1;
	}
    start=clock();
    // Predict class labels based on the decision tree
    for (int i = 0; i < row; i++)
	{
        int someInt = rules_func(dataArrayInt[i]);
		predictedClassLabelsInt.push_back(someInt);
	}
    end=clock();
    cout<<"Time Using: "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    dataTable.clear();
    // Print output
    ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
    // Print predictions
	printPredictions(givenClassLabelsInt, predictedClassLabelsInt);
    dlclose(libHandle);
	return 0;
}