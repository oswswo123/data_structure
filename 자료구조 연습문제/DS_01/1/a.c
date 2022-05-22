#include <stdio.h>

int sumAry1D_f1(int ary[], int size)
{
	int tmp=0;
	for (int i = 0; i<size; i++)
		tmp = tmp + ary[i];
	return tmp;
}
int sumAry1D_f2(int *ary, int size)
{
	int tmp=0;
	for (int i = 0; i<size; i++)
		tmp = tmp + *(ary+i);
	return tmp;
}
int sumAry1D_f3(int ary[6], int size)
{
	int tmp=0;
	for (int i = 0; size>i; size--)
		tmp = tmp + ary[(size - 1)];
	return tmp;
}

int main()
{
	int ary1D[] = { 1,2,3,4,5,6 };
	printf("sumAry1D_f1() %d\n", sumAry1D_f1(ary1D, 6));
	printf("sumAry1D_f2() %d\n", sumAry1D_f2(ary1D, 6));
	printf("sumAry1D_f3() %d\n", sumAry1D_f3(ary1D, 6));

	return 0;
}