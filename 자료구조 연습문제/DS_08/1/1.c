#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer first = NULL;

void insert(listPointer x, int a);
void delete(listPointer trail, listPointer x);
void printList(listPointer head);
listPointer find(listPointer head, int a);
void odddelete(listPointer head);

int main()
{
	FILE *f1;
	listPointer next = NULL;
	first = (listPointer *)malloc(sizeof(listNode));
	first->data = NULL;
	first->link = NULL;
	fopen_s(&f1, "input.txt", "r");
	int num;
	fscanf_s(f1, "%d", &num);
	while( !feof(f1) ) {
		next = find(first, num);
		insert(next, num);
		fscanf_s(f1, "%d", &num);
	}
	printList(first);

	odddelete(first);
	printf("After deleting nodes with odd value\n\n");
	printList(first);

	listPointer curr = first->link;
	while (curr != NULL) {
		listPointer buffer = curr->link;
		free(curr);
		curr = buffer;
	}
	free(first);

	return 0;
}

listPointer find(listPointer head, int a) {
	listPointer curr = head;
	while (head != NULL) {
		if (head->data > a) {
			return curr;
		}
		curr = head;
		head = head->link;
	}
	return curr;
}
void insert(listPointer x, int a) {
	listPointer temp;
	temp = malloc(sizeof(listNode));
	temp -> data = a;
	
	temp->link = x->link;
	x->link = temp;
}
void delete(listPointer trail, listPointer x) {
	trail->link = x->link;
	free(x);
}
void printList(listPointer head) {
	printf("The ordered list contains :\n");
	listPointer curr = head;
	head = head->link;
	while (head != NULL) {
		printf("(%8X,%4d,%8X)\n", curr->link, head->data, head->link);
		curr = head;
		head = head->link;
	}
	printf("\n");
}
void odddelete(listPointer head) {
	listPointer curr = head;
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
