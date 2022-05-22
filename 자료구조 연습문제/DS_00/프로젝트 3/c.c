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
		printf("파일을 읽는데 실패했습니다.");
		exit(1); // 파일 읽기 실패
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(f1, "%s %s %d", s[i].name,10, s[i].sex,3, &s[i].age);  // << 여기가 에러나는 부분!
	}
	for (int i = 0; i < 2; i++)
	{
		if (s[i].age < s[i + 1].age)
			a = i+1;
	}
	printf("  이름   성별   나이\n======================\n");
	for (int i = 0;i < 3;i++)
	{
		printf(" %s   %s     %d \n", s[i].name, s[i].sex, s[i].age);
	}
	printf("======================\n\n");
	printf(" << 최고령 사용자 >> \n %s   %s     %d \n", s[a].name, s[a].sex, s[a].age);


	return 0;
}