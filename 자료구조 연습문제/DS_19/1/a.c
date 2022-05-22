#include <stdio.h>
#include <stdlib.h>
#define MAX_DATA 100

typedef struct element {
	int key;
	char name[10];
	int grade;
}element;

element InsertSorting[MAX_DATA];
void insert(element e, element a[], int i);
void insertSort(element a[], int n);

int main()
{
	FILE *fp;
	int numberofinput, counter = 0;
	char inputstring[16];
	element temp;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d ", &numberofinput);
	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	while (!feof(fp)) {
		fgets(inputstring, 16, fp);
		sscanf_s(inputstring, "%d %s %d", &temp.key, temp.name, sizeof(temp.name), &temp.grade);
		insert(temp,InsertSorting, counter++);
		printf("(%3d, %s, %3d )\n", temp.key, temp.name, temp.grade);
	}
	fclose(fp);

	fopen_s(&fp, "output.txt", "w");
	printf("\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (int i = 1; i < counter + 1; i++) {
		fprintf(fp, "(%3d, %s, %3d)\n", InsertSorting[i].key, InsertSorting[i].name, InsertSorting[i].grade);
		printf("(%3d, %s, %3d)\n", InsertSorting[i].key, InsertSorting[i].name, InsertSorting[i].grade);
	}
	fclose(fp);

	return 0;
}

void insert(element e, element a[], int i) {
	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}
void insertSort(element a[], int n) {
	int j;
	for (j = 2; j <= n; j++) {
		element temp = a[j];
		insert(temp, a, j - 1);
	}
}