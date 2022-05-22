#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct node *treePointer;
typedef struct node {
	treePointer leftChild;
	char data;
	short int value;
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
treePointer copy(treePointer origianl);
void postOrderEval(treePointer node);
void inorder(treePointer first);		// print
void postfix(treePointer first);
void inorderchange(treePointer first, int i, int j, int k);

int main()
{
	FILE *fp;

	fopen_s(&fp, "input.txt", "r");
	root = createBinTree(fp);
	fclose(fp);

	printf("input string(postfix) : ");
	postfix(root);
	printf("\n");

	printf("find true condition\n");
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++){
		treePointer temp;
		temp = copy(root);
		inorderchange(temp, i, j, k);
		postOrderEval(temp);
		if (temp->value)
			printf("a = %d, b = %d, c = %d\n", i, j, k);
	}

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
treePointer copy(treePointer original) {
	treePointer temp;
	if (original) {
		temp = (node *)malloc(sizeof(node));
		temp->leftChild = copy(original->leftChild);
		temp->rightChild = copy(original->rightChild);
		temp->data = original->data;
		return temp;
	}
	return NULL;
}
void postOrderEval(treePointer node) {
	if (node) {
		postOrderEval(node->leftChild);
		postOrderEval(node->rightChild);
		switch (node->data) {
		case '~':
			node->value = !node->rightChild->value;
			break;
		case '&':
			node->value = node->rightChild->value && node->leftChild->value;
			break;
		case '|':
			node->value = node->rightChild->value || node->leftChild->value;
			break;
		default:
			break;
		}
	}
}
void inorder(treePointer first) {			// print
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
void inorderchange(treePointer first, int i, int j, int k) {
	if (first) {
		inorderchange(first->leftChild, i, j, k);
		if (first->data == 'a') {
			first->value = i;
		}
		if (first->data == 'b') {
			first->value = j;
		}
		if (first->data == 'c') {
			first->value = k;
		}
		inorderchange(first->rightChild, i, j, k);
	}
}