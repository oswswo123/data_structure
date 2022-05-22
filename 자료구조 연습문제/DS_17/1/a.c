#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define INF 1000

typedef struct element {
	int key;
	int u;
	int v;
}element;

element heap[MAX_VERTICES];
int n = 0, vertex = 0, cost = 0;
int *parent;

void insert_heap_edge(int u, int v, int weight);	// heap
void insert_min_heap(element e, int *n);
element pop(int *n);
void kruskal(int n);								// kruskal
int simpleFind(int i);
void simpleUnion(int i, int j);

int main()
{
	FILE *fp;
	int edge, ipu, ipv, ipkey, buffer;
	
	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d ", &edge);
	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d", &ipu, &ipv, &ipkey);
		insert_heap_edge(ipu, ipv, ipkey);
		//if (ipu < ipv)	buffer = ipv;
		//else			buffer = ipu;

		//if (vertex < buffer) vertex = buffer;
	}
	parent = (int *)malloc(sizeof(int) * (vertex + 1));
	for (int i = 0; i < vertex + 1; i++)
		parent[i] = -1;

	kruskal(edge);

	return 0;
}

void insert_heap_edge(int u, int v, int weight) {	// heap
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(e, &n);
}
void insert_min_heap(element e, int *n) {
	int i;
	if (*n == MAX_VERTICES - 1) {
		fprintf(stderr, "The heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (e.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = e;
}
element pop(int *n) {
	int parent, child;
	element item, temp;
	if (n == 0) {
		fprintf(stderr, "The heap is empty.\n");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key > heap[child + 1].key))
			child++;

		if (temp.key <= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}
void kruskal(int n) {								// kruskal
	int edge_accepted = 0;
	int uset, vset;
	element e;
	while (edge_accepted < vertex) {
		e = pop(&n);
		uset = simpleFind(e.u);
		vset = simpleFind(e.v);
		if (uset != vset) {
			printf("(%d,%d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			cost += e.key;
			simpleUnion(e.u, e.v);
		}
	}
	printf("\n최소비용 : %d\n\n", cost);

}
int simpleFind(int i) {
	while (parent[i] >= 0) {
		i = parent[i];
	}
	return i;
}
void simpleUnion(int i, int j) {
	if(parent[i] == -1 && parent[j] == -1)
		parent[i] = j;
	else {
		i = simpleFind(i);
		parent[i] = j;
	}
}