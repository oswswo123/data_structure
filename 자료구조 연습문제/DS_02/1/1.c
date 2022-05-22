#include <stdio.h>
#include <stdlib.h>

int func1(int *pi);
void func2(int *pi);
void func3(int *pi);

int main()
{
	int *pNum = (int *)malloc(sizeof(int));

	*pNum = func1(pNum);		//int ũ�⸸ŭ �����Ҵ� �ް�, 10�� ���� �� ������ ������ ����
	printf("%d\n", *pNum);

	func2(pNum);			// pNum�� ����Ű�� ���� 100���� ����
	printf("%d\n", *pNum);

	func3(pNum);			// pNum�� ����Ű�� ���� 200���� ����
	printf("%d\n", *pNum);
	free(pNum);

	return 0;
}

int func1(int *pi)
{
	pi = (int *)malloc(sizeof(int));
	if (!pi) {
		fprintf(stderr, "�޸𸮰� �����մϴ�.\n");
		exit(EXIT_FAILURE);
	}
	*pi = 10;
	return *pi;
}
void func2(int *pi)
{
	*pi = 100;
}
void func3(int *pi)
{
	*pi = 200;
}