#include <stdio.h>
#include <stdlib.h>
#include "Function.h"
#define MAX_SIZE 100

element initList[MAX_SIZE];
int inputnumber;

int main()
{
	FILE *fp;
	int counter = 1;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf_s(fp, "%d ", &inputnumber);
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &initList[counter++].key);
	}
	
	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	for (int i = 1; i < inputnumber + 1; i++)
		printf("%3d ", initList[i].key);

	printf("\n\n<<<<< executing itterative merge sort >>>>>\n");
	mergeSort(initList, inputnumber);
	
	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (int i = 1; i < inputnumber + 1; i++)
		printf("%3d ", initList[i].key);
	printf("\n\n");

	return 0;
}