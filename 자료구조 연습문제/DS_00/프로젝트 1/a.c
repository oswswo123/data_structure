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
	printf("�� ���� ���� �Է� >>");
	scanf_s("%d %d", &a, &b);
	printf("�μ��� ���� ��� : %d\n�μ��� ���� ��� : %d\n", hab(a,b), gob(a,b));
	return 0;
}