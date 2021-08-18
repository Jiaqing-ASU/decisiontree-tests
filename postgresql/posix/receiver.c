#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Treenode {
	int index; //index to compare, -1 if leaf
	double data; //value to compare if not leaf, return value if leaf
	bool isLeaf; //leaf or not
	int left; //left child index in tree array
	int right; //right child index in tree array
}Treenode;

int main(int argc, const char *argv[]){
	int size = (NUM_INT * sizeof(int) + NUM_DOUBLE * sizeof(double) + NUM_BOOL * sizeof(bool)) * 31;
	int fd = shm_open(NAME,O_RDONLY, 0666);
	if (fd < 0) {
		perror("shm_open()");
		return EXIT_FAILURE;
	}

	Treenode *treenodes = (Treenode*)mmap(0,size,PROT_READ, MAP_SHARED,fd,0);
	printf("tree mapped address: %p \n", treenodes);
	
	printf("%d \n",treenodes[1].index);
	munmap(treenodes,size);
	close(fd);
	return EXIT_SUCCESS;
}