#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

listPointer last;

void insertlist(listPointer n,int num);
void deletelist(listPointer n, listPointer trail);
void printlist();
void odddelete();

int main()
{
	last = (listNode *)malloc(sizeof(listNode));
	last->data = NULL;
	last->link = last;
	FILE *f1;
	int avil;
	fopen_s(&f1, "input.txt", "r");
	fscanf_s(f1, "%d", &avil);
	last->data = avil;
	while (!feof(f1)) {
		fscanf_s(f1, "%d", &avil);
		insertlist(last, avil);
	}
	printf("The Circularly Linked List contains:\n\n");
	printlist();
	odddelete();
	printf("\n\n");
	printf("After deleting nodes with odd value\n\n");
	printlist();

	listPointer curr, curr2;
	curr = last->link;
	while (curr != last) {
		listPointer temp;
		temp = curr->link;
		free(curr);
		curr = temp;
	}
	free(last);

	return 0;
}

void insertlist(listPointer n, int num) {
	listPointer temp;
	temp = (listNode *)malloc(sizeof(listNode));
	temp->data = num;
	temp->link = n->link;
	n->link = temp;
	last = temp;
}
void deletelist(listPointer x, listPointer trail) {
	trail->link = x->link;
	free(x);
}
void printlist() {
	listPointer temp;
	for (temp = last->link; temp != last; temp = temp->link){
		printf("(%8p,%5d,%8p)\n", temp, temp->data, temp->link);
	}
	printf("(%8p,%5d,%8p)\n", temp, temp->data, temp->link);
}
void odddelete() {
	listPointer temp,curr;
	curr = last;
	temp = last->link;
	while (temp != last) {
		if (temp->data % 2 == 1) {
			deletelist(temp, curr);
			temp = curr;
		}
		curr = temp;
		temp = temp->link;
	}
	if (temp->data % 2 == 1) {
		deletelist(temp, curr);
		last = curr;
	}
}