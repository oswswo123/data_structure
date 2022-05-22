#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
}node;
nodePointer header = NULL;

void dinsert(int num);
void ddelete(nodePointer spectornode, nodePointer deleted);
void fwdprint();
void bwdprint();
void fiftydelete();
void deleteallnode();

int main()
{
	header = (node *)malloc(sizeof(node));
	header->llink = header;
	header->rlink = header;
	header->data = NULL;

	FILE *f;
	int number;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "cannot open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(f)) {
		fscanf_s(f, "%d ", &number);
		dinsert(number);
	}

	printf("After creating a doubly linked circular list with a head node : \n");
	fwdprint();
	bwdprint();

	printf("After deleting numbers less than and equal to 50 : \n");
	fiftydelete();
	fwdprint();
	bwdprint();

	printf("After deleting all nodes except for the header node : \n");
	deleteallnode();
	fwdprint();
	bwdprint();

	return 0;
}

void dinsert(int num) {
	nodePointer newnode;
	newnode = (node *)malloc(sizeof(node));
	newnode->data = num;

	if (header->rlink == header) {
		newnode->llink = header;
		newnode->rlink = header;
		header->llink = newnode;
		header->rlink = newnode;
	}
	else {
		newnode->llink = header->llink;
		newnode->rlink = header;
		header->llink->rlink = newnode;
		header->llink = newnode;
	}
}
void ddelete(nodePointer spectornode, nodePointer deleted) {
	if (spectornode == deleted)
		printf("Deletion of header node not permitted.\n");
	else {
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}
}
void fwdprint() {
	nodePointer temp;
	temp = header->rlink;
	int counter = 0;

	printf("forward\n");
	while (temp != header) {
		printf("%d ", temp->data);
		temp = temp->rlink;
		counter++;
		if (counter == 10) {
			counter = 0;
			printf("\n");
		}
	}
	printf("\n");
}
void bwdprint() {
	nodePointer temp;
	temp = header->llink;
	int counter = 0;

	printf("backward\n");
	while (temp != header) {
		printf("%d ", temp->data);
		temp = temp->llink;
		counter++;
		if (counter == 10) {
			counter = 0;
			printf("\n");
		}
	}
	printf("\n\n");
}
void fiftydelete() {
	nodePointer curr, temp;
	curr = header->rlink;
	temp = header->rlink;

	while (temp != header) {
		if (temp->data <= 50) {
			curr = temp->llink;
			ddelete(header, temp);
			temp = curr;
		}
		temp = temp->rlink;
	}
}
void deleteallnode() {
	nodePointer temp;
	temp = header->rlink;
	
	while (temp != header) {
		ddelete(header, temp);
		temp = header->rlink;
	}
}