#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a[10], b[10];
	FILE *f1, *f2;
	fopen_s(&f1, "input-1.txt", "r");
	if (f1 == NULL)
	{
		printf("F1 ������ �дµ� �����Ͽ����ϴ�.");
		exit(1); // ���� �б� ����
	}
	for (int i = 0; i < 10; i++)
	{
		fscanf_s(f1, "%d", &a[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
	fclose(f1);
	printf("\n");

	fopen_s(&f2, "input-2.txt", "r");
	if (f2 == NULL)
	{
		printf("F2 ������ �дµ� �����Ͽ����ϴ�.");
		exit(1); // ���� �б� ����
	}
	for (int i = 0; i < 10; i++)
	{
		fscanf_s(f2, "%d", &b[i]);
	}
	for (int i = 0;i < 10;i++)
	{
		printf("%d ", b[i]);
	}
	fclose(f2);
	printf("\n");

	for (int i = 0;i < 10;i++)
	{
		printf("%d ", a[i]+b[i]);
	}
	printf("\n");

	return 0;
}