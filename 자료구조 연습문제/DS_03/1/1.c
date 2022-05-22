#include <stdio.h>
#include <stdlib.h>

int *make1dArray(int a);

int main()
{
	int *plist, num;

	printf("������ �迭�� ���� �Է��ϼ��� : ");
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
		fprintf(stderr, "�����Ҵ翡 �����Ͽ����ϴ�.");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < a; i++) {
		pi[i] = rand() % 100;
	}
	return pi;
}