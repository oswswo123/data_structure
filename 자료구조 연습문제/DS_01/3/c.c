#include <stdio.h>

int sumAry3D_f1(int ary[][2][3], int SEC, int ROW, int COL);
int sumAry3D_f2(int(*ary)[2][3], int SEC, int ROW, int COL);
int sumAry3D_f3(int ary[2][2][3], int SEC, int ROW, int COL);

int main()
{
	int ary[][2][3] = { { { 1,2,3 },{ 4,5,6 } } ,{ { 7,8,9 },{ 10,11,12 } } };

	printf("sumAry3D_f1() %d\n", sumAry3D_f1(ary, 2, 2, 3));
	printf("sumAry3D_f2() %d\n", sumAry3D_f2(ary, 2, 2, 3));
	printf("sumAry3D_f3() %d\n", sumAry3D_f3(ary, 2, 2, 3));

	return 0;
}

int sumAry3D_f1(int ary[][2][3], int SEC, int ROW, int COL)
{
	int tmp=0;
	for (int i = 0; i<SEC; i++)
		for (int j = 0; j<ROW; j++)
			for (int k = 0; k<COL; k++)
				tmp = tmp + ary[i][j][k];
	return tmp;
}
int sumAry3D_f2(int(*ary)[2][3], int SEC, int ROW, int COL)
{
	int tmp=0;
	for (int i = 0; i<SEC; i++)
		for (int j = 0; j<ROW; j++)
			for (int k = 0; k<COL; k++)
				tmp = tmp + (*(ary + i))[j][k];
	return tmp;
}
int sumAry3D_f3(int ary[2][2][3], int SEC, int ROW, int COL)
{
	int tmp=0;
	int i = SEC, j = ROW, k = COL;
	for (; i > 0; i--)
	{
		for (; j > 0; j--)
		{
			for (; k > 0; k--)
			{
				tmp = tmp + ary[i - 1][j - 1][k - 1];
			}
			k = COL;
		}
		j = ROW;
	}
	return tmp;
}