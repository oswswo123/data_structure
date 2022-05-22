#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define BUCKETS 10
#define DIGITS 4

typedef struct element {
	int key;
}element;

typedef struct QueueType* QueuePointer;
typedef struct QueueType {
	int key;
	QueuePointer link;
}QueueType;


QueuePointer queues[BUCKETS];
element a[MAX_SIZE];
int d, n;

void radix_sort(element list[], int n);
void enqueue(QueuePointer *queue, int item);
int dequeue(QueuePointer *queue);
int is_empty(QueuePointer queue);

int main()
{
	FILE *fp;
	int counter = 0;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d %d ", &d, &n);
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &a[counter++].key);
	}
	fclose(fp);

	printf("input data ---\n");
	for (int i = 0; i < n; i++)
		printf(" %3d", a[i].key);
	printf("\n\n");

	radix_sort(a, n);

	printf("\nresult ---\n");
	for (int i = 0; i < n; i++)
		printf(" %3d", a[i].key);
	printf("\n");

	return 0;
}

void radix_sort(element list[], int n) {
	int i, b, d, factor = 1, counter = 0;
	QueuePointer temp;

	for (b = 0; b < BUCKETS; b++)
		queues[b] = NULL;
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i].key / factor) % 10], list[i].key);

		printf("step %d 자리 ---\n\n", counter++);
		printf("Queue의 내용 ---\n");
		for (int l = 0; l < BUCKETS; l++) {
			printf("[%d] : ", l);
			temp = queues[l];
			while (temp) {
				printf(" %3d", temp->key);
				temp = temp->link;
			}
			printf("\n");
		}

		for (b = i = 0; b < BUCKETS; b++)
			while (is_empty(queues[b]) != 1)
				list[i++].key = dequeue(&queues[b]);
		factor *= 10;

		for (int k = 0; k < n; k++)
			printf(" %3d", list[k].key);
		printf("\n");
	}
}

void enqueue(QueuePointer *queue, int item) {
	QueuePointer temp;
	temp = (QueueType *)malloc(sizeof(QueueType));
	temp->key = item;

	if ((*queue) == NULL) {
		temp->link = NULL;
		(*queue) = temp;
	}
	else {
		QueuePointer round;
		round = (*queue);
		while (round->link != NULL)
			round = round->link;
		round->link = temp;
		temp->link = NULL;
	}
}
int dequeue(QueuePointer *queue) {
	QueuePointer temp;
	int item;

	item = (*queue)->key;
	temp = (*queue);
	(*queue) = (*queue)->link;
	free(temp);

	return item;
}
int is_empty(QueuePointer queue) {
	if (queue == NULL)
		return 1;
	else
		return 0;
}