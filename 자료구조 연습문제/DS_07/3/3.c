#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_s 10
#define name_s 10

struct s_data {
	char name[name_s];
}typedef s_data;

s_data stack[max_s];
int top[max_s];
int boundary[max_s];
int n = 0;

void push(int i, s_data item);
s_data pop(int i);
void stackFull(int i);
s_data stackEmpty(int i);
void sprint(int i);

int main()
{
	printf("How Many Stacks ? : ");
	scanf_s("%d", &n);
	getchar();
	printf("\n\n C Language program to implement the Multiple Stacks\n");
	printf("add stack_num(0-%d) name : add 0 kim\n", n - 1);
	printf("delete stack_num(0-%d) : delete 0\n", n - 1);
	printf("sprint stack_num(0-%d) : sprint 0\n", n - 1);
	printf("****************************************************\n");
	top[0] = boundary[0] = 0;
	for (int i = 1; i < n; i++)
		top[i] = boundary[i] = (max_s / n)*i;
	boundary[n] = max_s - 1;

	s_data item;
	char *input;
	char saparator[] = " ";
	char *buffer;
	char *commend;
	int stackNum;

	input = (char *)malloc(sizeof(char) * 26);
	buffer = (char *)malloc(sizeof(char) * 10);
	commend = (char *)malloc(sizeof(char) * 7);

	for (;;) {
		fgets(input, sizeof(char) * 25, stdin);
		commend = strtok_s(input, saparator, &buffer);
		if (strcmp(commend, "add") == 0) {
			sscanf_s(buffer, "%d %s", &stackNum, item.name, 10);
			if (stackNum > n - 1) {
				printf("Stack number error, try again!!\n");
				continue;
			}
			push(stackNum, item);
		}
		else if (strcmp(commend, "delete") == 0) {
			sscanf_s(buffer, "%d", &stackNum);
			if (stackNum > n - 1) {
				printf("Stack number error, try again!!\n");
				continue;
			}
			if (top[stackNum] == boundary[stackNum]) {
				stackEmpty(stackNum);
				continue;
			}
			printf("%s is popped from Stack No. %d\n", pop(stackNum).name, stackNum);
		}
		else if (strcmp(commend, "sprint") == 0) {
			sscanf_s(buffer, "%d", &stackNum);
			if (stackNum > n - 1) {
				printf("Stack number error, try again!!\n");
				continue;
			}
			sprint(stackNum);
		}
		else
			printf("Wrong command, try again!!\n");
	}

	return 0;
}

void push(int i, s_data item) {
	if (top[i] == boundary[i + 1]) {
		stackFull(i);
		return;
	}
	stack[top[i]] = item;
	printf("%s is Pushed in Stack No. %d\n", item.name, i);
	top[i]++;
}
s_data pop(int i) {
	if (top[i] == boundary[i])
		return stackEmpty(i);
	return stack[--top[i]];
}
void stackFull(int i) {
	fprintf(stderr, "Stack %d is Full\n", i);
}
s_data stackEmpty(int i) {
	fprintf(stderr, "Stack %d is Empty\n", i);
	return stack[i];
}
void sprint(int i) {
	for (int j = top[i] - 1; j >= boundary[i] ; j--)
		printf("%s\n", stack[j].name);
}
