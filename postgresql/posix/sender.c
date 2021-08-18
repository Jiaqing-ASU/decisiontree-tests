#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cassert>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <exception> 
#include <sstream>
using namespace std;

typedef struct Treenode {
	int index; //index to compare, -1 if leaf
	double data; //value to compare if not leaf, return value if leaf
	bool isLeaf; //leaf or not
	int left; //left child index in tree array
	int right; //right child index in tree array
}Treenode;

int main(int argc, const char *argv[]){
	string inputFilePath = argv[1]; //input csv file path
	ifstream inFile(inputFilePath, ios::in);
	int num_array;
	int size;
	string lineString;
	vector<string> valueArray;
	vector<int> indexArray;
	vector<double> dataArray;
	vector<bool> isLeafArray;
	vector<int> leftArray;
	vector<int> rightArray;
	while (getline(inFile, lineString))
	{
		stringstream ss(lineString);
		string str;
		while (getline(ss, str, ',')){
			valueArray.push_back(str);
		}
	}

	for (int i = 0; i < valueArray.size(); i++){
        if(i == 0){
        	stringstream ss;
        	ss << valueArray.at(i);
        	ss >> num_array;
        	size = (NUM_INT * sizeof(int) + NUM_DOUBLE * sizeof(double) + NUM_BOOL * sizeof(bool)) * num_array;
        }
        else if(i%5 == 1){
        	stringstream ss;
        	int thisValue;
        	ss << valueArray.at(i);
        	ss >> thisValue;
        	indexArray.push_back(thisValue);
        }
        else if(i%5 == 2){
        	stringstream ss;
        	double thisValue;
        	ss << valueArray.at(i);
        	ss >> thisValue;
        	dataArray.push_back(thisValue);
        }
        else if(i%5 == 3){
        	stringstream ss;
        	bool thisValue;
        	ss << valueArray.at(i);
        	ss >> thisValue;
        	isLeafArray.push_back(thisValue);
        }
        else if(i%5 == 4){
        	stringstream ss;
        	int thisValue;
        	ss << valueArray.at(i);
        	ss >> thisValue;
        	leftArray.push_back(thisValue);
        }
        else if(i%5 == 0){
        	stringstream ss;
        	int thisValue;
        	ss << valueArray.at(i);
        	ss >> thisValue;
        	rightArray.push_back(thisValue);
        }
        else{
        	cout << "Error analysis input tree file" << endl;
        }
	}

	int fd = shm_open(NAME,O_CREAT | O_EXCL | O_RDWR, 0666);
	if (fd < 0) {
		if (errno == EACCES){
			printf("1");
		} else if (errno == EEXIST){
			printf("2");
		} else if (errno == EINTR){
			printf("3");
		} else if (errno == EINVAL){
			printf("4");
		} else if (errno == EMFILE){
			printf("5");
		} else if (errno == ENAMETOOLONG){
			printf("6");
		} else if (errno == ENFILE){
			printf("7");
		} else if (errno == ENOENT){
			printf("8");
		} else if (errno == ENOSPC){
			printf("9");
		}
		perror("shm_open()");
		return EXIT_FAILURE;
	}

	ftruncate(fd, size);
	Treenode *treenodes = (Treenode*)mmap(0,size,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	printf("tree mapped address: %p \n", treenodes);

	for(int i = 0; i < num_array; i++){
		treenodes[i].index = indexArray.at(i);
		treenodes[i].data = dataArray.at(i);
		treenodes[i].isLeaf = isLeafArray.at(i);
		treenodes[i].left = leftArray.at(i);
		treenodes[i].right = rightArray.at(i);
	}
    
	munmap(treenodes,size);
	close(fd);
	return EXIT_SUCCESS;
}