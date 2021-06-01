#include "header.h"

int main(int argc, const char *argv[])
{
    clock_t start,end;
    msi mattributes;
    msd mresult;
    mresult["setosa"] = 1.0;
    mresult["versicolor"] = 2.0;
    mresult["virginica"] = 3.0;
    mattributes["Sepal.Length"] = 0;
    mattributes["Sepal.Width"] = 1;
    mattributes["Petal.Length"] = 2;
    mattributes["Petal.Width"] = 3;
    mattributes["Species"] = 4;
    ifstream inputFile;// Input file stream
	string singleInstance;// Single line read from the input file 
	vvs dataTable;// Input data in the form of a vector of vector of strings
    vvd dataTableDouble;// Input data in the form of a vector of vector of Doubles
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
    int column = dataTable[0].size()-1;
    double dataArrayDouble[row][column];
    // Stores the predicted class labels for each row in Int
    vd predictedClassLabels;
    // Stores the given class labels in the test data in Int
    vd givenClassLabels;
    // Store given class labels in vector of strings named givenClassLabels
    // Transfer input data from string to Int using map
    for (int i = 1; i < dataTable.size(); i++)
    {
        string data = dataTable[i][dataTable[0].size()-1];
        double dataDouble = mresult[data];
        givenClassLabels.push_back(dataDouble);
        for (int j = 0; j < dataTable[0].size()-1; j++){
            dataArrayDouble[i-1][j] = std::stod(dataTable[i][j]);
        }
    }
    void* libHandle = dlopen("librules.so", RTLD_LAZY);
    if(!libHandle)
	{
		printf("open lib error\n");
		cout<<dlerror()<<endl;
		return -1;
	}
    typedef double (* rules_func_t)(double * a);
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
        double someDouble = rules_func(dataArrayDouble[i]);
		predictedClassLabels.push_back(someDouble);
	}
    end=clock();
    cout<<"Time Using: "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    dataTable.clear();
    // Print output
    ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
    // Print predictions
	printPredictions(givenClassLabels, predictedClassLabels);
    dlclose(libHandle);
	return 0;
}