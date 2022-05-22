#include <stdio.h>
#define TURE 1
#define FALSE 0
#define MAX_NAME 30

struct human {
	char name[MAX_NAME];
	int age;
	int salary;
}typedef human;

int humansEqual(human *a, human *b);

int main() 
{
	human person1, person2;

	printf("Input person1's name, age, salary :\n");
	fgets(person1.name, sizeof(person1.name), stdin);
	person1.name[strlen(person1.name) - 1] = '\0';
	scanf_s("%d", &person1.age);
	scanf_s("%d", &person1.salary);

	getchar();                        // buffer
	printf("Input person2's name, age, salary :\n");
	fgets(person2.name, sizeof(person2.name), stdin);
	person2.name[strlen(person2.name) - 1] = '\0';
	scanf_s("%d", &person2.age);
	scanf_s("%d", &person2.salary);

	if (humansEqual(&person1, &person2))
		printf("두 사람은 동일인물입니다.\n");
	else
		printf("두 사람은 다른인물입니다.\n");
	
	return 0;
}

int humansEqual(human *a, human *b) 
{
	if (strcmp(a->name, b->name))
		return FALSE;
	if (a->age !=  b->age)
		return FALSE;
	if (a->salary != b->salary)
		return FALSE;

	return TURE;
}