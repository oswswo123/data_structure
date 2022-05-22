#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int sortcounter = 0;
int QuickSorting[MAX_SIZE];
void quickSort(int a[], int left, int right, int n);

int main()
{
	FILE *fp;
	int numberofinput, input, counter = 0;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d ", &numberofinput);
	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &input);
		QuickSorting[counter] = input;
		printf("%3d", QuickSorting[counter]);
		counter++;
	}

	printf("\n\nexecution of quick sort...\n");
	quickSort(QuickSorting, 0, counter-1, counter);
	printf("calls of quick sort : %d\n\n", sortcounter);
	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (int i = 0; i < counter; i++)
		printf("%3d", QuickSorting[i]);
	printf("\n");

	fopen_s(&fp, "output.txt", "w");
	fprintf(fp, "%d\n", counter);
	for (int i = 0; i < counter; i++)
		fprintf(fp, "%3d", QuickSorting[i]);
	fclose(fp);

	return 0;
}

void quickSort(int a[], int left, int right, int n) {
	sortcounter++;
	int pivot, i, j;
	int temp;
	if (left < right) {
		i = left;
		j = right+1;
		pivot = a[left];
		printf("pivot = %2d :", pivot);
		for (int k = 0; k < n; k++)
			printf("%3d", QuickSorting[k]);
		printf("\n");
		do {
			do i++; 
			while (a[i] < pivot);
			do j--; 
			while (a[j] > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		
		quickSort(a, left, j - 1, n);
		quickSort(a, j + 1, right, n);
	}
}