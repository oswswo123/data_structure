#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7
#define INF 1000

int weight[MAX_VERTICES][MAX_VERTICES];
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int path[MAX_VERTICES];
int vertex = 0, edge;

void makeweight(int edge1, int edge2, int weight1);
void shortestPath(int v, int weight[][MAX_VERTICES], int distance[], int n, short int found[]);
int choose(int distance[], int n, short int found[]);
void printpath(int n);

int main()
{
	FILE *fp;
	int e1, e2, iw;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			weight[i][j] = INF;
	for (int i = 0; i < MAX_VERTICES; i++)
		weight[i][i] = 0;

	fscanf_s(fp, "%d", &edge);
	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d", &e1, &e2, &iw);
		makeweight(e1, e2, iw);
	}

	shortestPath(0, weight, distance, vertex + 1, found);
	for (int i = 0; i < vertex + 1; i++) {
		if(distance[i])
			printf("distance[0-%d] = %2d : ",i ,distance[i]);
		printpath(i);
		printf("\n");
	}

	return 0;
}

void makeweight(int edge1, int edge2, int weight1) {
	int temp;
	
	weight[edge1][edge2] = weight1;
	weight[edge2][edge1] = weight1;

	if (edge1 < edge2)
		temp = edge2;
	else
		temp = edge1;
	if (vertex < temp)
		vertex = temp;
}
void shortestPath(int v, int weight[][MAX_VERTICES], int distance[], int n, short int found[]) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = FALSE;
		distance[i] = weight[v][i];
	}
	found[v] = TRUE;
	distance[v] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
			if (!found[w])
				if (distance[u] + weight[u][w] < distance[w]) {
					distance[w] = distance[u] + weight[u][w];
					path[w] = u;
				}
	}
}
int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;
	min = INF;
	minpos = -1;
	for(i = 0; i<n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void printpath(int n) {
	if (n != 0) {
		int k = n;
		n = path[n];
		printpath(n);
		printf(" <%d -> %d> ", path[k], k);
	}
}