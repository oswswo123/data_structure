#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 100

typedef struct node *nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}listNode;

int vertex;
int edge;
char direct;
nodePointer adjList[MAX_VERTEX];

void uinsert(int x, int y);
void dinsert(int x, int y);
void makeadjList(FILE *fp);
void listprint(nodePointer np);

int main()
{
	FILE *fp;
	char input[10];
	int x, y;

	fopen_s(&fp, "input.txt", "r");
	makeadjList(fp);

	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	for (int i = 0; i < vertex; i++) {
		printf("adjList[%d] : ", i);
		listprint(adjList[i]);
		printf("\n");
	}

	return 0;
}

void uinsert(int x, int y) {
	nodePointer temp1, temp2;
	temp1 = (listNode *)malloc(sizeof(listNode));
	temp2 = (listNode *)malloc(sizeof(listNode));

	temp1->data = y;
	temp2->data = x;

	if (adjList[x] == NULL) {
		temp1->link = NULL;
		adjList[x] = temp1;
	}
	else {
		temp1->link = adjList[x];
		adjList[x] = temp1;
	}

	if (adjList[y] == NULL) {
		temp2->link = NULL;
		adjList[y] = temp2;
	}
	else {
		temp2->link = adjList[y];
		adjList[y] = temp2;
	}
}
void dinsert(int x, int y) {
	nodePointer temp;
	temp = (listNode *)malloc(sizeof(listNode));
	
	temp->data = y;

	if (adjList[x] == NULL) {
		temp->link = NULL;
		adjList[x] = temp;
	}
	else {
		temp->link = adjList[x];
		adjList[x] = temp;
	}
}
void makeadjList(FILE *fp) {
	int x, y;
	fscanf_s(fp, "%c", &direct);
	fscanf_s(fp, "%d %d", &vertex, &edge);

	if (direct == 'u') {
		while (!feof(fp)) {
			fscanf_s(fp, "%d %d", &x, &y);
			uinsert(x, y);
		}
	}
	else if (direct == 'd') {
		while (!feof(fp)) {
			fscanf_s(fp, "%d %d", &x, &y);
			dinsert(x, y);
		}
	}
}
void listprint(nodePointer np) {
	while (np) {
		printf(" %d ", np->data);
		np = np->link;
	}
}