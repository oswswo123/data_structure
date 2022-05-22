#include <stdio.h>
#include <stdlib.h>

int **make2dArray(int a, int b);
void freeAry2d(int **array, int a);

int main()
{
	int **plist, rows, cols;

	printf("이차원 배열의 수를 입력하세요 : ");
	scanf_s("%d %d", &rows, &cols);
	plist = make2dArray(rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) 
			printf("plist[%d][%d] = %d  ", i, j, plist[i][j]);

	freeAry2d(plist, rows);

	return 0;
}

int **make2dArray(int a, int b) 
{
	int **pi;

	pi = (int *)malloc((sizeof(int *)) * a);

	for (int i = 0; i < a; i++) {
		pi[i] = (int *)malloc( ((sizeof(int *)) * b) );
	}

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			pi[i][j] = rand() % 100;
		}
	}

	return pi;
}
void freeAry2d(int **array, int a)
{
	for (int i = 0; i < a; i++)
		free(array[i]);
}