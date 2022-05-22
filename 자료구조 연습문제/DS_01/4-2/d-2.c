#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
	if (!(p=malloc(sizeof(s)))) { \
		fprintf(stderr, "메모리가 부족합니다."); \
		exit(EXIT_FAILURE); \
	} // 메모리 부족, 동적 할당 실패

int main()
{
	int i, *pi;
	float f, *pf;
	pi = (int *)malloc(sizeof(int));
	pf = (float *)malloc(sizeof(float));
	MALLOC(pi, sizeof(int));
	MALLOC(pf, sizeof(float));
	*pi = 1024;
	*pf = 3.14;
	printf("an integer = %d, a float = %f\n", *pi, *pf);
	free(pi);
	free(pf);

	return 0;
}