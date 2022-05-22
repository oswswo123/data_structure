#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}tNode;
treePointer root;
treePointer queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void addq(treePointer element);			// queue
treePointer deleteq();
void queueFull();
treePointer queueEmpty();
treePointer getFront();
treePointer createNode(char data);		// tree
treePointer createCompBinTree(FILE *fp);
void insert(treePointer *pRoot, treePointer pNode);
int hasBothChild(treePointer pNode);
void inorder(treePointer first);		// print
void preorder(treePointer first);
void postorder(treePointer first);

int main()
{
	FILE *f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "cannot file open!\n");
		exit(EXIT_FAILURE);
	}

	printf("creating a complete binary tree\n\n");
	createCompBinTree(f);
	
	printf("three binary tree traversals\ninorder traversal     : ");
	inorder(root);
	printf("\npreorder traversal    : ");
	preorder(root);
	printf("\npostorder traversal   : ");
	postorder(root);
	printf("\n");

	return 0;
}

void addq(treePointer element) {		// queue
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	else {
		rear++;
		queue[rear] = element;
	}
}
treePointer deleteq() {
	if (rear == front)
		queueEmpty();
	else {
		front++;
		return queue[front];
	}
}
void queueFull() {
	fprintf(stderr, "Queue is Full!\n");
	exit(EXIT_FAILURE);
}
treePointer queueEmpty() {
	fprintf(stderr, "QUEUE is Empty!\n");
	exit(EXIT_FAILURE);
}
treePointer getFront() {
	return queue[front+1];
}
treePointer createNode(char data) {		// tree
	treePointer temp;
	temp = (tNode *)malloc(sizeof(tNode));
	temp->data = data;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	return temp;
}
treePointer createCompBinTree(FILE *fp) {
	char sampleC;
	treePointer samplePointer;
	while (!feof(fp)) {
		fscanf_s(fp, "%c ", &sampleC);
		samplePointer = createNode(sampleC);
		insert(&root, samplePointer);
	}

	return root;
}
void insert(treePointer *pRoot, treePointer pNode) {
	treePointer frontnode;
	if (!(*pRoot))
		(*pRoot) = pNode;
	else {
		frontnode = getFront();
		if (frontnode->leftChild == NULL)
			frontnode->leftChild = pNode;
		else if (frontnode->rightChild == NULL)
			frontnode->rightChild = pNode;
		else
			hasBothChild(pNode);
	}
	addq(pNode);
}
int hasBothChild(treePointer pNode) {
	treePointer frontnode;
	deleteq();
	frontnode = getFront();
	frontnode->leftChild = pNode;
}
void inorder(treePointer first){		// print
	if (first) {
		inorder(first->leftChild);
		printf("%c", first->data);
		inorder(first->rightChild);
	}
}
void preorder(treePointer first) {
	if (first) {
		printf("%c", first->data);
		preorder(first->leftChild);
		preorder(first->rightChild);
	}
}
void postorder(treePointer first) {
	if (first) {
		postorder(first->leftChild);
		postorder(first->rightChild);
		printf("%c", first->data);
	}
}