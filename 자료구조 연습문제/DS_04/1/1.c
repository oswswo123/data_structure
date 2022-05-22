#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 20
#define MAX_ROW 20
#define MAX_VAL 100

struct sparseMatrix {
	int col;
	int row;
	int value;
}typedef sparseMatrix;

int compare(int a, int b);
void sortingMatrix(sparseMatrix a[], int b);
void transMatrix(sparseMatrix *a, sparseMatrix *b);

int main()
{
	int valNum;
	printf("원소의 개수를 쓰시오 .. ");
	scanf_s("%d", &valNum);
	int Matrix[20][20];
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			Matrix[i][j] = 0;

	sparseMatrix *sparse;
	sparse = (sparseMatrix *)malloc((sizeof(sparseMatrix) * (valNum+1)));

	sparse[0].col = 20;
	sparse[0].row = 20;
	sparse[0].value = valNum;

	for (int i = 0; i < valNum; i++) {
		sparse[i + 1].col = rand() % MAX_COL;
		sparse[i + 1].row = rand() % MAX_ROW;
		for (int j = 0; j < i; j++) {
			while (sparse[i + 1].col == sparse[j + 1].col && sparse[i + 1].row == sparse[j + 1].row) {
				sparse[i + 1].col = rand() % MAX_COL;
				sparse[i + 1].col = rand() % MAX_ROW;
				j = 0;
			}
		}
		sparse[i + 1].value = (rand() % MAX_VAL) + 1;
	}

	sortingMatrix(sparse, valNum);

	for (int i = 0; i < valNum; i++)
		Matrix[sparse[i + 1].col][sparse[i + 1].row] = sparse[i + 1].value;

	printf("Random generated Matrix(20x20)\n");
	for (int i = 0; i < MAX_COL; i++) {						//출력
		for (int j = 0; j < MAX_ROW; j++)
			printf("%2d ", Matrix[i][j]);
		printf("\n");
	}
	printf("Sparce Matrix\n");
	for (int i = 0; i <= valNum; i++)
		printf("%4d %4d %4d\n", sparse[i].col, sparse[i].row, sparse[i].value);

	free(sparse);

	return 0;
}

int compare(int a, int b) {
	if (a > b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
void sortingMatrix(sparseMatrix a[], int b) {

	for (int i = 1; i < b + 1; i++) {
		for (int j = i; j < b + 1; j++) {
			if (compare(a[i].col, a[j].col) == -1)
				transMatrix(&a[i], &a[j]);
		}
	}
	for (int i = 1; i < b + 1; i++) {
		for (int j = i; j < b + 1; j++) {
			if ((compare(a[i].row, a[j].row) == -1) && (a[i].col == a[j].col))
				transMatrix(&a[i], &a[j]);
		}
	}
}
void transMatrix(sparseMatrix *a, sparseMatrix *b) {
	sparseMatrix temp;
	temp = *a;
	*a = *b;
	*b = temp;
}