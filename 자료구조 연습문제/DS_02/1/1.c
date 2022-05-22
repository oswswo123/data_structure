#include <stdio.h>
#include <stdlib.h>

int func1(int *pi);
void func2(int *pi);
void func3(int *pi);

int main()
{
	int *pNum = (int *)malloc(sizeof(int));

	*pNum = func1(pNum);		//int 크기만큼 동적할당 받고, 10을 지정 후 정수형 포인터 리턴
	printf("%d\n", *pNum);

	func2(pNum);			// pNum이 가리키는 것을 100으로 수정
	printf("%d\n", *pNum);

	func3(pNum);			// pNum이 가리키는 것을 200으로 수정
	printf("%d\n", *pNum);
	free(pNum);

	return 0;
}

int func1(int *pi)
{
	pi = (int *)malloc(sizeof(int));
	if (!pi) {
		fprintf(stderr, "메모리가 부족합니다.\n");
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