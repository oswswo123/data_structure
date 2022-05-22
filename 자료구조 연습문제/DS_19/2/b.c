#include <stdio.h>
#include <stdlib.h>
#define MAX_DATA 100

int ShellSorting[MAX_DATA];
void insertSort(int a[], int first, int last, int gap);
void shellSort(int a[], int n);

int main()
{
	FILE *fp;
	int numberofinput, counter = 0;
	int input;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d ", &numberofinput);
	printf("list[] data\n");
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &input);
		ShellSorting[counter] = input;
		printf("%5d", ShellSorting[counter++]);
	}
	printf("\n");

	fclose(fp);
	shellSort(ShellSorting, counter);

	return 0;
}

void insertSort(int a[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = a[i];
		for (j = i - gap; j >= first && key < a[j]; j = j - gap)
			a[j + gap] = a[j];
		a[j + gap] = key;
	}
}
void shellSort(int a[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0)gap++;
		for (i = 0; i < gap; i++) {
			insertSort(a, i, n - 1, gap);
			/*if (i == gap - 1) {						// Ãâ·ÂºÎºÐ
				printf("\ngap is %5d ===>\n", gap);
				for (int j = 0; j < n; j++)
					printf("%5d", a[j]);
				printf("\n");							// ½Å°æ²¨µµµÊ
			}*/
		}
	}
}