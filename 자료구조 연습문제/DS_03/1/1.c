#include <stdio.h>
#include <stdlib.h>

int *make1dArray(int a);

int main()
{
	int *plist, num;

	printf("일차원 배열의 수를 입력하세요 : ");
	scanf_s("%d", &num);
	plist = make1dArray(num);

	for (int i = 0; i < num; i++)
		printf("plist[%d] = %d  ", i, plist[i]);
	printf("\n");
	free(plist);

	return 0;
}

int *make1dArray(int a) {
	int *pi;
	pi = (int *)malloc((sizeof(int)) * a);
	if (!(pi)) {
		fprintf(stderr, "동적할당에 실패하였습니다.");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < a; i++) {
		pi[i] = rand() % 100;
	}
	return pi;
}