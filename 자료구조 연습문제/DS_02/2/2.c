#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

void main()
{
	int n = 2000;
	int *a;
	double gap;
	clock_t start,end;

	a = (int *)malloc(sizeof(int)*MAX_SIZE);

	for (int i = 0; i < n; i++) {
		a[i] = n-i;
		printf("%d ", a[i]);
	}
	printf("\n");

	start = clock();
	sort(a,n);
	end = clock();
	gap = ( (double) (end - start) / CLOCKS_PER_SEC );
	printf("�������� ���\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n�������Ŀ� �ɸ� �ð� = %f��\n", gap);

	FILE *F;
	fopen_s(&F, "out.txt", "a");
	fprintf(F, " %d   %f\n", n, gap);
	fclose(F);
	free(a);

	printf("\n");


}