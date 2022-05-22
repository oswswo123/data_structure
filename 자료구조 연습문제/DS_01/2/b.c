#include <stdio.h>

int sumAry2D_f1(int ary[][3], int ROW, int COL)
{
	int tmp=0;
	for (int i = 0; i<ROW; i++)
		for (int j = 0; j<COL; j++)
			tmp = tmp + ary[i][j];
	return tmp;
}

int sumAry2D_f2(int (*ary)[3], int ROW, int COL)
{
	int tmp=0;
	for (int i = 0; i<ROW; i++)
		for (int j = 0; j<COL; j++)
			tmp = tmp + (*(ary + i))[j];
	return tmp;
}
int sumAry2D_f3(int ary[2][3], int ROW, int COL)
{
	int tmp=0;
	int i = ROW, j = COL;
	for (; i > 0; i--)
	{
		for (; j > 0; j--)
		{
			tmp = tmp + ary[i - 1][j - 1];
		}
		j = COL;
	}
	return tmp;
}


int main()
{
	int ary[][3] = { { 1,2,3 },{ 4,5,6 } };

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary, 2, 3));
	
	return 0;
}