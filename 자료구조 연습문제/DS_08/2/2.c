#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
	int data;
	struct listNode *link;
}listNode;
listNode *first = NULL;

void insert(listNode *x, int a);
void delete(listNode *trail, listNode *x);
void printList(listNode *head);
listNode *find(listNode *head, int a);
void odddelete(listNode *head);

int main()
{
	FILE *f1;
	listNode *next = NULL;
	first = (listNode *)malloc(sizeof(listNode));
	first->data = NULL;
	first->link = NULL;
	fopen_s(&f1, "input.txt", "r");
	int num;
	fscanf_s(f1, "%d", &num);
	while (!feof(f1)) {
		next = find(first, num);
		insert(next, num);
		fscanf_s(f1, "%d", &num);
	}
	printList(first);

	odddelete(first);
	printf("After deleting nodes with odd value\n\n");
	printList(first);

	listNode *curr = first->link;
	while (curr != NULL) {
		listNode *buffer = curr->link;
		free(curr);
		curr = buffer;
	}
	free(first);

	return 0;
}

listNode *find(listNode *head, int a) {
	listNode *curr = head;
	while (head != NULL) {
		if (head->data > a) {
			return curr;
		}
		curr = head;
		head = head->link;
	}
	return curr;
}
void insert(listNode *x, int a) {
	listNode *temp;
	temp = (listNode *)malloc(sizeof(listNode));
	temp->data = a;

	temp->link = x->link;
	x->link = temp;
}
void delete(listNode *trail, listNode *x) {
	trail->link = x->link;
	free(x);
}
void printList(listNode *head) {
	printf("The ordered list contains :\n");
	listNode *curr = head;
	head = head->link;
	while (head != NULL) {
		printf("(%8X,%4d,%8X)\n", curr->link, head->data, head->link);
		curr = head;
		head = head->link;
	}
	printf("\n");
}
void odddelete(listNode *head) {
	listNode *curr = head;
	head = head->link;
	while (head != NULL) {
		if ((head->data) % 2 == 1) {
			delete(curr, head);
			head = curr->link;
		}
		else {
			curr = head;
			head = head->link;
		}
	}
}
