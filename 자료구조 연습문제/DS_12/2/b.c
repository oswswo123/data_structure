#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}tNode;

treePointer root;

treePointer stack[MAX_STACK_SIZE];		//stack
int top = -1;

treePointer queue[MAX_QUEUE_SIZE];		// circular queue
int front = 0, rear = 0;

char expr[81];

void push(treePointer element);			// stack
treePointer pop();
void stackFull();
treePointer stackEmpty();
void addq(treePointer element);			// circular queue
treePointer deleteq();
void queueFull();
treePointer queueEmpty();
void createBinTree(FILE *fp);			// tree
treePointer createNode(char item);
void inorder(treePointer first);		// print
void preorder(treePointer first);
void postorder(treePointer first);
void iterInorder(treePointer first);
void levelOrder(treePointer first);

int main()
{
	FILE *f;

	fopen_s(&f, "input.txt", "r");
	while (!feof(f)) {
		fscanf_s(f, "%s", expr, 80);
	}
	fclose(f);
	
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) : %s\n", expr);
	fopen_s(&f, "input.txt", "r");
	createBinTree(f);
	fclose(f);
	
	printf("\niterative inorder traversal   : ");
	iterInorder(root);
	printf("\nlevel order traversal         : ");
	levelOrder(root);
	printf("\n");

	return 0;
}

void push(treePointer element) {			// stack
	if (top == MAX_STACK_SIZE - 1)
		stackFull();
	else {
		top++;
		stack[top] = element;
	}
}
treePointer pop() {
	if (top == -1)
		stackEmpty();
	else {
		treePointer temp;
		temp = stack[top];
		top--;
		return temp;
	}
}
void stackFull() {
	fprintf(stderr, "Stack is Full!!\n");
	exit(EXIT_FAILURE);
}
treePointer stackEmpty() {
	return NULL;
}
void addq(treePointer element) {			// circular queue
	if ((rear + 1) % MAX_QUEUE_SIZE == front)
		queueFull();
	else {
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		queue[rear] = element;
	}
}
treePointer deleteq(){
	if (rear == front)
		queueEmpty();
	else {
		front = (front + 1) % MAX_QUEUE_SIZE;
		return queue[front];
	}
}
void queueFull() {
	fprintf(stderr, "Queue is Full!!\n");
	exit(EXIT_FAILURE);
}
treePointer queueEmpty() {
	return NULL;
}
void createBinTree(FILE *fp) {			// tree
	if (fp == NULL) {
		fprintf(stderr, "cannot open file!!\n");
		exit(EXIT_FAILURE);
	}
	char input;
	treePointer temp, right, left;
	while (!feof(fp)) {
		fscanf_s(fp, "%c ", &input);
		switch(input) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			temp = createNode(input);
			right = pop();
			left = pop();
			temp->rightChild = right;
			temp->leftChild = left;
			push(temp);
			break;
		default:
			temp = createNode(input);
			push(temp);
			break;
		}
	}
	root = pop();
	printf("creating its binary tree\n");
}
treePointer createNode(char item) {
	treePointer temp;
	temp = (tNode *)malloc(sizeof(tNode));
	temp->data = item;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	return temp;
}
void inorder(treePointer first) {		// print
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
void iterInorder(treePointer first) {
	for (;;) {
		for (; first; first = first->leftChild)
			push(first);
		first = pop();
		if (!first) break;
		printf("%c", first->data);
		first = first->rightChild;
	}
}
void levelOrder(treePointer first) {
	if (!first) return;
	addq(first);
	for (;;) {
		first = deleteq();
		if (first) {
			printf("%c", first->data);
			if (first->leftChild)
				addq(first->leftChild);
			if (first->rightChild)
				addq(first->rightChild);
		}
		else break;
	}
}