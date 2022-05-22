#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 6
#define MAX_ROW 6
#define valNum 8

struct sparseMatrix {
	int col;
	int row;
	int value;
}typedef sparseMatrix;

int compare(int a, int b);
void sortingMatrix(sparseMatrix *a, int b);
void transMatrix(sparseMatrix *a, sparseMatrix *b);
void fastTranspose1(sparseMatrix *a, sparseMatrix *b);
void fastTranspose2(sparseMatrix *a, sparseMatrix *b);
void attachMatrix(sparseMatrix *s, int **m);
void printMatrix(char c, int **m, int col, int row);

int main()
{
	FILE *F1, *F2;
	fopen_s(&F1, "a.txt", "r");
	fopen_s(&F2, "b.txt", "w");
	sparseMatrix *sparseA, *sparseB;
	int **matrixA, **matrixB;

	sparseA = (sparseMatrix *)malloc((valNum + 1) * sizeof(sparseMatrix));
	sparseB = (sparseMatrix *)malloc((valNum + 1) * sizeof(sparseMatrix));
	matrixA = (int **)calloc(MAX_COL, sizeof(int));
	for (int i = 0; i < MAX_ROW; i++)
		matrixA[i] = (int *)calloc(MAX_ROW, sizeof(int));
	matrixB = (int **)calloc(MAX_COL, sizeof(int));
	for (int i = 0; i < MAX_ROW; i++)
		matrixB[i] = (int *)calloc(MAX_ROW, sizeof(int));

	for (int i = 0; i<valNum + 1; i++)
		fscanf_s(F1, "%d %d %d", &sparseA[i].col, &sparseA[i].row, &sparseA[i].value);

	fastTranspose1(sparseA, sparseB);
	fastTranspose2(sparseA, sparseB);
	sortingMatrix(sparseB, valNum);
	attachMatrix(sparseA, matrixA);
	attachMatrix(sparseB, matrixB);

	for (int i = 0; i < valNum + 1; i++)
		fprintf_s(F2, "%2d %2d %4d\n", sparseB[i].col, sparseB[i].row, sparseB[i].value);

	printMatrix('A', matrixA, MAX_COL, MAX_ROW);
	printf("\n");
	printMatrix('B', matrixB, MAX_COL, MAX_ROW);

	fclose(F1);
	fclose(F2);
	free(sparseA);
	free(sparseB);
	for (int i = 0; i<MAX_ROW; i++)
		free(matrixA[i]);
	free(matrixA);
	for (int i = 0; i<MAX_ROW; i++)
		free(matrixB[i]);
	free(matrixB);

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
void sortingMatrix(sparseMatrix *a, int b) {

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
void fastTranspose1(sparseMatrix *a, sparseMatrix *b) {

	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a->col, numTerms = a->value;
	b->row = numCols;
	b->col = a->row;
	b->value = numTerms;

	if (numTerms > 0) { // nonzero matrix
		for (i = 0;i < numCols;i++)
			rowTerms[i] = 0;
		for (i = 1;i <= numTerms;i++)
			rowTerms[(a+i)->col]++;
		startingPos[0] = 1;
		for (i = 1;i < numCols;i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[(a+i)->col]++;
			(b+j)->row = (a+i)->col;
			(b+j)->col = (a+i)->row;
			(b+j)->value = (a+i)->value;
		}
	}
}
void fastTranspose2(sparseMatrix *a, sparseMatrix *b) {

	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = (*a).col, numTerms = (*a).value;
	(*b).row = numCols;
	(*b).col = (*a).row;
	(*b).value = numTerms;

	if (numTerms > 0) { // nonzero matrix
		for (i = 0;i < numCols;i++)
			rowTerms[i] = 0;
		for (i = 1;i <= numTerms;i++)
			rowTerms[(*(a+i)).col]++;
		startingPos[0] = 1;
		for (i = 1;i < numCols;i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[(*(a+i)).col]++;
			(*(b+j)).row = (*(a+i)).col;
			(*(b+j)).col = (*(a+i)).row;
			(*(b+j)).value = (*(a+i)).value;
		}
	}
}
void attachMatrix(sparseMatrix *s, int **m)
{
	for (int i = 1; i < valNum + 1; i++)
		m[s[i].col][s[i].row] = s[i].value;
}
void printMatrix(char c, int **m, int col, int row) {
	printf("%c\n", c);
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++)
			printf("%3d ", m[i][j]);
		printf("\n");
	}
}