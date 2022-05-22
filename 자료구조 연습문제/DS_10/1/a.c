#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

int main() 
{
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i = 0, j = 0, n = 0;

	FILE *f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "cannot file open\n");
		exit(EXIT_FAILURE);
	}
	fscanf_s(f, "%d", &n);

	printf("current size of S : %d\n", n);
	printf("S = { ");
	for (int i = 0; i < n; i++)
		printf("%d, ", i);
	printf("}\ninput pairs : ");
	while (!feof(f)) {
		fscanf_s(f, "%d %d", &i, &j);
		printf("%dR%d ", i, j);
	}
	fclose(f);

	printf("\n");

	fopen_s(&f, "input.txt", "r");
	fscanf_s(f, "%d", &n);

	for (int i = 0; i < n; i++) {
		out[i] = TRUE;
		seq[i] = NULL;
	}

	// Phase 1: Input the equivalence pairs
	fscanf_s(f, "%d %d", &i, &j);
	while (!feof(f)) {
		x = (node *)malloc(sizeof(node));
		x->data = j;	x->link = seq[i];	seq[i] = x;

		y = (node *)malloc(sizeof(node));
		y->data = i;	y->link = seq[j];	seq[j] = y;
		fscanf_s(f, "%d %d", &i, &j);
	}
	x = (node *)malloc(sizeof(node));
	x->data = j;	x->link = seq[i];	seq[i] = x;

	x = (node *)malloc(sizeof(node));
	x->data = i;	x->link = seq[j];	seq[j] = x;

	// Phase 2: output the equivalence classes
	for (i = 0; i < n; i++) {
		if (out[i]) {
			printf("\nNew Class: %5d", i);
			out[i] = FALSE;		// set class to true
			x = seq[i];		top = NULL;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j);
						out[j] = FALSE;
						y = x->link;	x->link = top;
						top = x;		x = y;		// push in the stack
					}
					else x = x->link;
				}
				if (!top) break;	// empty stack
				x = seq[top->data];
				top = top->link;	// pop
			}
		}
	}
	printf("\n");

	fclose(f);

	return 0;
}