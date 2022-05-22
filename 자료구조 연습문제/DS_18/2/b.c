#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

typedef struct node *nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
}node;
typedef struct hdnodes{
	int count;
	nodePointer link;
}hdnodes;
hdnodes graph[MAX_VERTICES];

int vertex = 0;
void topSort(hdnodes graph[], int n);
void linkedge(int edge1, int edge2);

int main()
{
	FILE *fp;
	int edge1, edge2;

	for (int i = 0; i < MAX_VERTICES - 1; i++) {
		graph[i].count = 0;
		graph[i].link = NULL;
	}

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp)) {
		fscanf_s(fp, "%d %d", &edge1, &edge2);
		linkedge(edge1, edge2);
	}

	topSort(graph, vertex+1);
	printf("\n");

	return 0;
}

void linkedge(int edge1, int edge2) {
	nodePointer temp;
	temp = (node *)malloc(sizeof(node));
	temp->vertex = edge2;

	if (graph[edge1].link == NULL) {
		temp->link = NULL;
		graph[edge1].link = temp;
	}
	else {
		temp->link = graph[edge1].link;
		graph[edge1].link = temp;
	}

	graph[edge2].count++;

	int num;
	if (edge1 < edge2)	num = edge2;
	else				num = edge1;
	if (vertex < num) vertex = num;
}
void topSort(hdnodes graph[], int n) {
	int i, j, k, top;
	nodePointer ptr;
	top = -1;
	for(i=0; i<n; i++)
		if (!graph[i].count) {
			//graph[i].count = top;
			top = i;
		}
	for (i = 0; i < n; i++)
		if (top == -1) {
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated. \n");
			exit(EXIT_FAILURE);
		}
		else {
			j = top;
			top = graph[top].count; // cycle ÆÇº°
			printf("%d -> ", j);
			for (ptr = graph[j].link; ptr; ptr = ptr->link) {
				k = ptr->vertex;
				graph[k].count--;
				if (!graph[k].count) {
					//graph[k].count = top;
					top = k;
				}
			}
		}
}