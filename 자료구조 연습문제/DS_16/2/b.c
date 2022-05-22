#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100
#define MAX_QUEUE_SIZE 500

short int visited[MAX_VERTICES];
int numvertex, numedge;

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer *graph;

listPointer queue, rear, front;

void addq(int i);		// queue
int deleteq();
int queueEmpty();		// queue
void bfs(int v);
void makegraphlist(FILE *fp);
listPointer createlist(int item);
void addlist(listPointer temp1, listPointer temp2);
void printlist(listPointer temp);

int main()
{
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file!!\n");
		exit(EXIT_FAILURE);
	}
	makegraphlist(fp);

	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	for (int i = 0; i < numvertex; i++) {
		printf("graph[%d] : ", i);
		printlist(graph[i]);
		printf("\n");
	}
	
	printf("\n<<<<<<<<<< Breadth First Search >>>>>>>>>>\n");
	for (int i = 0; i < numvertex; i++) {
		printf("graph[%d] : ", i);
		bfs(i);
		for (int j = 0; j < numvertex; j++)
			visited[j] = FALSE;
		printf("\n");
	}

	

	return 0;
}

void addq(int i) {		// queue
	listPointer temp;
	temp = (listNode *)malloc(sizeof(listNode));
	temp->data = i;
	temp->link = NULL;

	if (front)
		rear->link = temp;
	else
		front = temp;
	rear = temp;
}
int deleteq() {
	int item;
	listPointer temp = front;

	if (!temp) {
		return queueEmpty();
	}
	else {
		item = temp->data;
		front = temp->link;
		free(temp);
		return item;
	}
}
int queueEmpty() {		// queue
	return NULL;
}
void bfs(int v) {
	listPointer w;
	front = rear = NULL;
	printf("%5d", v);
	visited[v] = TRUE;
	addq(v);
	while (front) {
		v = deleteq();
		for(w = graph[v]; w; w=w->link)
			if (!visited[w->data]) {
				printf("%5d", w->data);
				addq(w->data);
				visited[w->data] = TRUE;
			}
	}
}
void makegraphlist(FILE *fp) {
	fscanf_s(fp, "%d %d", &numvertex, &numedge);
	graph = (listNode *)malloc(sizeof(listNode) * numvertex);
	for (int i = 0; i < numvertex; i++)
		graph[i] = NULL;
	for (int i = 0; i < numvertex; i++)
		visited[i] = FALSE;

	listPointer a, b;
	int firstnum, secondnum;
	while (!feof(fp)) {
		fscanf_s(fp, "%d %d", &firstnum, &secondnum);
		a = createlist(firstnum);
		b = createlist(secondnum);
		addlist(a, b);
	}
}
listPointer createlist(int item) {
	listPointer temp;
	temp = (listNode *)malloc(sizeof(listNode));
	temp->data = item;
	temp->link = NULL;
	return temp;
}
void addlist(listPointer temp1, listPointer temp2) {
	if (graph[temp1->data] == NULL) {
		temp2->link = NULL;
		graph[temp1->data] = temp2;
	}
	else {
		temp2->link = graph[temp1->data];
		graph[temp1->data] = temp2;
	}

	if (graph[temp2->data] == NULL) {
		temp1->link = NULL;
		graph[temp2->data] = temp1;
	}
	else {
		temp1->link = graph[temp2->data];
		graph[temp2->data] = temp1;
	}
}
void printlist(listPointer temp) {
	while (temp) {
		printf("%5d", temp->data);
		temp = temp->link;
	}
}