#include <stdio.h>
#include <stdlib.h>

struct student {
	char name[10];
	char sex[3];
	int age;
};

int main()
{
	struct student s[3];
	FILE *f1;
	int a=0;
	
	fopen_s(&f1, "input.txt", "r");
	if (f1 == NULL)
	{
		printf("������ �дµ� �����߽��ϴ�.");
		exit(1); // ���� �б� ����
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(f1, "%s %s %d", s[i].name,10, s[i].sex,3, &s[i].age);  // << ���Ⱑ �������� �κ�!
	}
	for (int i = 0; i < 2; i++)
	{
		if (s[i].age < s[i + 1].age)
			a = i+1;
	}
	printf("  �̸�   ����   ����\n======================\n");
	for (int i = 0;i < 3;i++)
	{
		printf(" %s   %s     %d \n", s[i].name, s[i].sex, s[i].age);
	}
	printf("======================\n\n");
	printf(" << �ְ�� ����� >> \n %s   %s     %d \n", s[a].name, s[a].sex, s[a].age);


	return 0;
}