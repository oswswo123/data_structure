#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, *pi;
	float f, *pf;
	pi = (int *)malloc(sizeof(int));
	pf = (float *)malloc(sizeof(float));
	if (((pi = (int *)malloc(sizeof(int))) == NULL)||((pf = (float *)malloc(sizeof(float)))==NULL))
	{
		fprintf(stderr, "�޸𸮰� �����մϴ�.");
		exit(EXIT_FAILURE); // �޸� ����, ���� �Ҵ� ����
	}
	*pi = 1024;
	*pf = 3.14;
	printf("an integer = %d, a float = %f\n", *pi, *pf);
	free(pi);
	free(pf);

	return 0;
}