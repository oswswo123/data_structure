#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int initList[MAX_SIZE];
int sorted[MAX_SIZE];
int inputnumber;

void merge(int list[], int left, int mid, int right);
void merge_sort(int list[], int left, int right);

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
		fscanf_s(fp, "%d ", &initList[counter++]);
	}
	for (int i = 1; i < inputnumber+1; i++)
		printf("%3d ", initList[i]);
	printf("\n\n");

	printf("<<<<< executing recursive merge sort >>>>>\n");
	merge_sort(initList, 1, inputnumber);

	return 0;
}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	
	printf("call merge(list, left = %2d, mid = %2d, right = %2d)\n", left, mid, right);

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		printf("call merge_sort(list, left = %2d, mid = %2d)\n", left, mid);
		merge_sort(list, left, mid);
		
		printf("call merge_sort(list, mid+1 = %2d, right = %2d)\n", mid + 1, right);
		merge_sort(list, mid + 1, right);
		
		merge(list, left, mid, right);
		printf("result : ");
		for (int i = 1; i < inputnumber + 1; i++)
			printf("%3d ", initList[i]);
		printf("\n\n");
	}
}