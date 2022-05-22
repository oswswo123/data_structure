#include <stdio.h>

int hab(int a, int b)
{
	return a + b;
}
int gob(int a, int b)
{
	return a * b;
}

int main()
{
	int a, b, c, d;
	printf("두 개의 정수 입력 >>");
	scanf_s("%d %d", &a, &b);
	printf("두수의 덧셈 결과 : %d\n두수의 곱셈 결과 : %d\n", hab(a,b), gob(a,b));
	return 0;
}