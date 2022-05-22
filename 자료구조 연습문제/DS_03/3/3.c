#include <stdio.h>
#include <stdlib.h>

int sumAry2D_f1(int ary[][3], int rows, int cols);
int sumAry2D_f2(int(*ary)[3], int rows, int cols);
int sumAry2D_f3(int ary[2][3], int rows, int cols);

int sumAry2D_f4(int **ary, int rows, int cols);
int sumAry2D_f5(int ***ary, int rows, int cols);

void freeAry2D(int **ary, int a);

int main()
{
	int ary2D[][3] = { {1,2,3}, {4,5,6} };

	int **ary = (int **)malloc(sizeof(int *) * 2);
	for (int r = 0; r < 2; r++)
		ary[r] = (int *)malloc(sizeof(int) * 3);

	for (int r = 0; r < 2; r++)
		for (int c = 0; c < 3; c++)
			ary[r][c] = r + c;

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));

	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary, 2, 3));

	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary2D, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary2D, 2, 3));

	freeAry2D(ary, 2);

	return 0;
}

int sumAry2D_f1(int ary[][3], int rows, int cols) 
{
	int temp = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp = temp + ary[i][j];
	return temp;
}
int sumAry2D_f2(int(*ary)[3], int rows, int cols) 
{
	int temp = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp = temp + ary[i][j];
	return temp;
}
int sumAry2D_f3(int ary[2][3], int rows, int cols)
{
	int temp = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp = temp + ary[i][j];
	return temp;
}

int sumAry2D_f4(int **ary, int rows, int cols)
{
	int temp = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp = temp + ary[i][j];
	return temp;
}
int sumAry2D_f5(int ***ary, int rows, int cols)
{
	int temp = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp = temp + (*ary)[i][j];
	return temp;
}

void freeAry2D(int **ary, int a)
{
	for (int i = 0; i < a; i++)
		free(ary[i]);
}