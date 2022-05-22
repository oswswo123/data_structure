#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 5
#define MAX_NAME_SIZE 10

struct element{
	int id;
	char name[MAX_NAME_SIZE];
}typedef element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void addq(element item);
element deleteq();
void queueFull();
element queueEmpty();
void shiftelement(element *a, element *b);
void qprint();
int compare(char *a);

int main ()
{
	element item;
	char *input;
	char seperator[] = " ";
	char *commend;
	char *buffer;

	input = (char *)malloc(sizeof(char) * 31);
	commend = (char *)malloc(sizeof(char) * 5);
	buffer = (char *)malloc(sizeof(char) * 25);

	printf("<<linear queue operations where MAX_QUEUE_SIZE_ is 5>>\n");
	printf("add 1 Jung\ndelete\nqprint\n\n*******************************************************\n");
	for (;;){
		fgets(input, sizeof(char) * 30, stdin);
		input[strlen(input) - 1] = '\0';
		commend = strtok_s(input,seperator,&buffer);
		switch(compare(commend)){
		case 2:
			qprint();
			break;
		case 1:
			sscanf_s(buffer,"%d %s", &item.id, item.name, MAX_NAME_SIZE);
			addq(item);
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

void addq(element item){
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	queue[++rear] = item;
}
element deleteq(){
	if (front == rear)
		return queueEmpty();
	return queue[++front];
}
void queueFull(){
	if (front == -1 && rear == MAX_QUEUE_SIZE - 1){
		fprintf(stderr,"Queue is full, cannot add element!\n");
		for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
			element example = deleteq();
			printf("%d %s\n", example.id, example.name);
		}
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < MAX_QUEUE_SIZE-(front+1); i++) {
		shiftelement(&queue[i], &queue[(front+1)+i]);
	}
	rear = 3 - front;
	front = -1;
}
element queueEmpty(){
	fprintf(stderr, "Queue is empty, cannot remove element!\n");
	exit(EXIT_FAILURE);
}
void shiftelement(element *a, element *b){
	element temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int compare(char *a){
	if ((strcmp(a,"add")) == 0)
		return 1;
	else if ((strcmp(a,"delete")) == 0)
		return 0;
	else if ((strcmp(a,"qprint")) == 0)
		return 2;
	else
		return -1;
}
void qprint() {
	for (int i = front + 1; i<rear + 1; i++)
		printf("%d %s\n", queue[i].id, queue[i].name);
}