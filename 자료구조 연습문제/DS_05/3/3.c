#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 10

struct element {
	int id;
	char name[MAX_NAME_SIZE];
}typedef element;

element *queue;
int capacity = 3;
int rear = 0;
int front = 0;

void addq(element item);
element deleteq();
void queueFull();
element queueEmpty();
void shiftelement(element *a, element *b);
void qprint();
int compare(char *a);

int main()
{
	queue = (element *)malloc(sizeof(element)*MAX_QUEUE_SIZE);
	element item;
	char *input;
	char seperator[] = " ";
	char *commend;
	char *buffer;

	input = (char *)malloc(sizeof(char) * 31);
	commend = (char *)malloc(sizeof(char) * 5);
	buffer = (char *)malloc(sizeof(char) * 25);

	printf("<< Circular queue operations where MAX_QUEUE_SIZE is 3 >>\n");
	printf("add 1 Jung\ndelete\nqprint\n\n*********************************************************\n");
	for (;;) {
		fgets(input, sizeof(char) * 30, stdin);
		input[strlen(input) - 1] = '\0';
		commend = strtok_s(input, seperator, &buffer);
		switch (compare(commend)) {
		case 2:
			qprint();
			break;
		case 1:
			sscanf_s(buffer, "%d %s", &item.id, item.name, MAX_NAME_SIZE);
			addq(item);
			if (rear == front) {
				if (rear == 0)
					rear = MAX_QUEUE_SIZE - 1;
				else
					rear--;
			}
			break;
		case 0:
			deleteq();
			break;
		case -1:
			printf("wrong command! try again!\n");
		}
	}

	return 0;
}

void addq(element item) {
	rear = (rear + 1) % capacity;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}
element deleteq() {
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
void queueFull() {
	fprintf(stderr, "queue is full, not added\n");
}
element queueEmpty() {
	fprintf(stderr, "Queue is empty, cannot remove element!\n");
	exit(EXIT_FAILURE);
}
int compare(char *a) {
	if ((strcmp(a, "add")) == 0)
		return 1;
	else if ((strcmp(a, "delete")) == 0)
		return 0;
	else if ((strcmp(a, "qprint")) == 0)
		return 2;
	else
		return -1;
}
void qprint() {
	if (rear < front) {
		for (int i = front + 1; i < MAX_QUEUE_SIZE; i++)
			printf("%d %s\n", queue[i].id, queue[i].name);
		for (int i = 0; i <= rear; i++)
			printf("%d %s\n", queue[i].id, queue[i].name);
	}
	else if (rear > front) {
		for (int i = front + 1; i <= rear; i++)
			printf("%d %s\n", queue[i].id, queue[i].name);
	}
	else
		return;
}