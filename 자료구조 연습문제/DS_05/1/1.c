#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 10

struct element{
	int id;
	char name[MAX_NAME_SIZE];
}typedef element;

void push(element item);
element pop();
void stackFull();
element stackEmpty();
int compare(char *a);
void sprint();

element stack[MAX_STACK_SIZE];
int top = -1;

int main()
{
	element item;
	char *input;
	char *commend;
	char seperator[] = " ";
	char *buffer;

	input = (char *)malloc(sizeof(char) * 31);
	commend = (char *)malloc(sizeof(char) * 5);
	buffer = (char *)malloc(sizeof(char) * 25);
	
	printf("<<stack operations where MAX_STACK_SIZE is 5>>\n");
	printf("push 1 Jung\npop\nsprint\n\n**********************************************\n");
	for (;;){
		fgets(input, sizeof(char) * 30, stdin);
		input[strlen(input) - 1] = '\0';
		commend = strtok_s(input,seperator,&buffer);
		switch (compare(commend)){
		case 2:
			sprint();
			break;
		case 0:
			sscanf_s(buffer, "%d %s", &item.id, item.name, sizeof(char)*MAX_NAME_SIZE);
			push(item);
			break;
		case 1:
			pop();
			break;
		case -1:
			printf("wrong command! try again!\n");
		}
	}

	return 0;
}

void push(element item){
	if (top >= MAX_STACK_SIZE-1)
		stackFull();
	stack[++top]=item;
}
element pop(){
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}
void stackFull(){
	fprintf(stderr,"Stack is full, cannot add element\n");
	for (int i = 0;i < MAX_STACK_SIZE; i++) {
		element example = pop();
		printf("%d %s\n", example.id, example.name);
	}
	exit(EXIT_FAILURE);
}
element stackEmpty(){
	fprintf(stderr, "Stack is empty, cannot remove element\n");
	exit(EXIT_FAILURE);
}
int compare(char *a){
	if (strcmp(a, "sprint") == 0)
		return 2;
	if (strcmp(a,"push") == 0)
		return 0;
	else if (strcmp(a,"pop") == 0)
		return 1;
	return -1;
}
void sprint() {
	for (int i = 0; i < top + 1; i++)
		printf("%d %s\n", stack[top - i].id, stack[top - i].name);
}