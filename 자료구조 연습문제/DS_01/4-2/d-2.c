#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
	if (!(p=malloc(sizeof(s)))) { \
		fprintf(stderr, "�޸𸮰� �����մϴ�."); \
		exit(EXIT_FAILURE); \
	} // �޸� ����, ���� �Ҵ� ����

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