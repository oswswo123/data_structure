#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 15

struct element {
	int id;
	char name[MAX_NAME_SIZE];
}typedef element;

element *queue;
int capacity = 2;
int rear = 0;
int front = 0;

element deleteq();
void addq(element item);
void queueFull();
element queueEmpty();
void qprint();
void copy(element *a, element *b, element *c);

int main()
{
	queue = (element *)malloc(sizeof(element) * capacity);

	element item;
	char *input;
	char saparator[] = " ";
	char *commend;
	char *buffer;

	input = (char *)malloc(sizeof(char) * 31);
	commend = (char *)malloc(sizeof(char) * 7);
	buffer = (char *)malloc(sizeof(char) * 23);

	printf("<< circular queue operations using dynamic allocated array, where the initial capacity is 2 >>\n");
	printf("add 1 Jung\ndelete\nqprint\n\n**************************************************\n");

	for (;;) {
		fgets(input, sizeof(char) * 30, stdin);
		input[strlen(input) - 1] = '\0';
		commend = strtok_s(input, saparator, &buffer);
		if (strcmp(commend, "add") == 0) {
			sscanf_s(buffer, "%d %s", &item.id, item.name, MAX_NAME_SIZE);
			addq(item);
		}
		else if (strcmp(commend, "delete") == 0)
			deleteq();
		else if (strcmp(commend, "qprint") == 0)
			qprint();
		else
			fprintf(stderr, "Wrong commend! Enter proper commend!\n");
	}

	return 0;
}

element deleteq() {
	element item;
	if (front == rear)
		return queueEmpty();	// return an error key
	front = (front + 1) % capacity;
	return queue[front];
}
void addq(element item) {
	rear = (rear + 1) % capacity;
	if (front == rear)
		queueFull();	// double capacity
	queue[rear] = item;
}
void queueFull() {
	int start;
	element *newQueue;
	newQueue = (element *)malloc(2 * capacity * sizeof(element));

	start = (front + 1) % capacity;
	if (start < 2)
		copy(queue + start, queue + start + capacity - 1, newQueue);
	else {
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 1;
	capacity *= 2;
	free(queue);
	queue = newQueue;
	printf("queue capacity is doubled.\ncurrent queue capacity is %d\n", capacity);
}
element queueEmpty() {
	fprintf(stderr, "queue is Empty! can't delete!\n");
	exit(EXIT_FAILURE);
}
void qprint() {
	if (front < rear)
		for (int i = front + 1; i <= rear; i++)
			printf("%d  %s\n", queue[i].id, queue[i].name);
	else if (front > rear) {
		for (int i = front + 1; i <= capacity - 1; i++)
			printf("%d  %s\n", queue[i].id, queue[i].name);
		for (int i = 0; i <= rear; i++)
			printf("%d  %s\n", queue[i].id, queue[i].name);
	}
	else
		return;
}
void copy(element *a, element *b, element *c) {
	while (a != b)
		*c++ = *a++;
}