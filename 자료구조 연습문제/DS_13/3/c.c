#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
}element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int *n);
element pop();

int main()
{
	FILE *fp;
	element input, output;

	fopen_s(&fp, "input.txt", "r");
	printf("***** insertion into a max heap *****\n");
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &input.key);
		push(input,&n);
	}
	fclose(fp);

	printf("***** deletion from a max heap *****\n");
	for (; n > 0;) {
		output = pop(&n);
		printf("delet data = %d\n", output.key);
		for (int i = 1; i <= n; i++)
			printf("%d ", heap[i]);
		printf("\n");
	}
	return 0;
}

void push(element item, int *n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
	for (int j = 1; j <= (*n); j++)
		printf("%d ", heap[j].key);
	printf("\n");
}
element pop(int *n) {
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}