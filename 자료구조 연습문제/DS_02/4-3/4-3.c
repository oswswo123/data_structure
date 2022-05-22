#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

void main()
{
	int n = 2000, repet = 0;
	int *a;
	double gap;
	clock_t start, end;

	a = (int *)malloc(sizeof(int)*MAX_SIZE);

	for (int i = 0; i < n; i++) {
		a[i] = rand() % 2001 ;
		printf("%d ", a[i]);
	}
	printf("\n");

	start = clock();
	sort(a, n);
	end = clock();
	repet++;
	gap = ((double)(end - start) / CLOCKS_PER_SEC);

	do {
		repet++;
		for (int i = 0; i < n; i++)
			a[i] = rand() % 2001 ;
		sort(a, n);
	} while (clock() - start < 1000);
	printf("선택정렬 결과\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n선택정렬에 걸린 시간 = %f초, 반복횟수 = %d회\n", gap, repet);

	FILE *F;
	fopen_s(&F, "out.txt", "a");
	fprintf(F, " %d   %f     %d\n", n, gap, repet);
	fclose(F);
	free(a);

	printf("\n");

}