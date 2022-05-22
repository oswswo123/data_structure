#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct node *treePointer;
typedef struct node {
	treePointer leftChild;
	char data;
	treePointer rightChild;
}node;

treePointer root;
treePointer stack[MAX_STACK_SIZE];
int top = -1;

void push(treePointer element);			// stack
treePointer pop();
void stackFull();
treePointer stackEmpty();
treePointer createBinTree(FILE *f);		// tree
treePointer createNode(char item);
void inorder(treePointer first);		// print
void postfix(treePointer first);

int main()
{
	FILE *fp;

	fopen_s(&fp, "input.txt", "r");
	root = createBinTree(fp);
	fclose(fp);

	printf("input string(postfix) : ");
	postfix(root);
	printf("\ninorder traversal     : ");
	inorder(root);

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
	if (top <= -1)
		stackEmpty();
	else
		return stack[top--];
}
void stackFull() {
	fprintf(stderr, "Stack is Full!!\n");
	exit(EXIT_FAILURE);
}
treePointer stackEmpty() {
	return NULL;
}
treePointer createBinTree(FILE *f) {		// tree
	treePointer temp;
	char input;
	while (!feof(f)) {
		fscanf_s(f, "%c ", &input);
		switch (input) {
		case '~':
			temp = createNode(input);
			temp->rightChild = pop();
			push(temp);
			break;
		case '&':
		case '|':
			temp = createNode(input);
			temp->rightChild = pop();
			temp->leftChild = pop();
			push(temp);
			break;
		default:
			temp = createNode(input);
			push(temp);
			break;
		}
	}
	printf("creating its binary tree\n");
	return pop();
}
treePointer createNode(char item) {
	treePointer temp;
	temp = (node *)malloc(sizeof(node));
	temp->data = item;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	return temp;
}
void inorder(treePointer first) {
	if (first) {
		inorder(first->leftChild);
		printf("%c", first->data);
		inorder(first->rightChild);
	}
}
void postfix(treePointer first) {
	if (first) {
		postfix(first->leftChild);
		postfix(first->rightChild);
		printf("%c", first->data);
	}
}