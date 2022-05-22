#include <stdio.h>
#include <stdlib.h>
#include "Function.h"
#define MAX_SIZE 100

typedef struct element {
	int key;
	char name[10];
	int grade;
}element;

element list[MAX_SIZE];
int inputnumber;

int main()
{
	FILE *fp;
	int counter = 0;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d ", &inputnumber);
	while (!feof(fp)) {
		fscanf_s(fp, "%d %s %d",
			&list[counter].key, list[counter].name, 10, &list[counter].grade);
		counter++;
	}
	fclose(fp);

	printf("<<<<<<<<<< input List >>>>>>>>>>\n");
	for (int i = 0; i < inputnumber; i++)
		printf("( %2d, %s, %2d)\n", list[i].key, list[i].name, list[i].grade);
	printf("\n");

	bubble_sort(list, inputnumber);

	printf("<<<<<<<<<< Result Sorted List >>>>>>>>>>\n");
	for (int i = 0; i < inputnumber; i++)
		printf("( %2d, %s, %2d)\n", list[i].key, list[i].name, list[i].grade);

	fopen_s(&fp, "output.txt", "w");
	for(int i=0; i<inputnumber; i++)
		fprintf(fp,"( %2d, %s, %2d)\n", list[i].key, list[i].name, list[i].grade);
	fclose(fp);

	return 0;
}