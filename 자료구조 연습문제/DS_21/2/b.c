#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct element {
	int key;
}element;

int rear[10];
int front[10];
int link[MAX_SIZE];
element a[MAX_SIZE];
int d, n;

int radixSort(element a[], int link[], int d, int r, int n);
int digit(int item, int i, int r);

int main()
{
	FILE *fp;
	int counter = 1, first;
	
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d %d ", &d, &n);
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &a[counter++].key);
	}
	fclose(fp);

	first = radixSort(a, link, d, 10, n);

	fopen_s(&fp, "output.txt", "w");
	for (int i = first; i != 0; i = link[i])
		fprintf(fp, "%3d ", a[i].key);
	fclose(fp);

	return 0;
}

int radixSort(element a[], int link[], int d, int r, int n) {
	int i, bin, current, first, last, counter = 1;
	first = 1;
	for (i = 1; i < n; i++)
		link[i] = i + 1;
	link[n] = 0;

	printf("***************** initial chain *****************\n");
	printf("          ");
	for (int k = 1; k < n + 1; k++)
		printf(" [%d]", k);
	printf("\n   link : ");
	for (int k = 1; k < n + 1; k++)
		printf(" %3d", link[k]);
	printf("\n      a : ");
	for (int k = 1; k < n + 1; k++)
		printf(" %3d", a[k].key);
	printf("\n  first :  %3d\n", first);
	printf(" result : ");
	for (int k = first; k != 0; k = link[k])
		printf(" %3d", a[k].key);
	printf("\n\n");

	for (i = d - 1; i >= 0; i--) {
		for (bin = 0; bin < r; bin++)
			front[bin] = 0;
		for (current = first; current; current = link[current]) {
			bin = digit(a[current].key, i, r);
			if (front[bin] == 0)
				front[bin] = current;
			else
				link[rear[bin]] = current;
			rear[bin] = current;
		}
		for (bin = 0; !front[bin]; bin++);
		first = front[bin];
		last = rear[bin];

		for(bin++; bin<r; bin++)
			if (front[bin]) {
				link[last] = front[bin];
				last = rear[bin];
			}
		link[last] = 0;

		printf("******************** pass %d ********************\n", counter++);
		printf("          ");
		for (int k = 1; k < n + 1; k++)
			printf(" [%d]", k);
		printf("\n   link : ");
		for (int k = 1; k < n + 1; k++)
			printf(" %3d", link[k]);
		printf("\n      a : ");
		for (int k = 1; k < n + 1; k++)
			printf(" %3d", a[k].key);
		printf("\n  first :  %3d\n", first);
		printf(" result : ");
		for (int k = first; k != 0; k = link[k])
			printf(" %3d", a[k].key);
		printf("\n\n");

		for (int k = 0; k < r; k++)
			if (front[k] == 0)
				rear[k] = 0;
		printf("          ");
		for (int k = 0; k < r; k++)
			printf(" [%d]", k);
		printf("\n   rear : ");
		for (int k = 0; k < r; k++)
			printf(" %3d", rear[k]);
		printf("\n  front : ");
		for (int k = 0; k < r; k++)
			printf(" %3d", front[k]);
		printf("\n\n");
	}
	return first;
}
int digit(int item, int i, int r) {
	int data;

	for (int j = d - i - 1; j > 0; j--)
		r *= 10;
	data = item % r;
	data = data / (r/10);

	return data;
}