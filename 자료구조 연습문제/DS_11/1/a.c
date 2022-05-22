#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}tNode;
treePointer root;

void insert(treePointer *first, treePointer frontnode, treePointer newnode);
treePointer createNode(char A);
void inorder(treePointer first);
void preorder(treePointer first);
void postorder(treePointer first);

int main()
{
	treePointer A, B, C, D, E;
	A = createNode('A');
	B = createNode('B');
	C = createNode('C');
	D = createNode('D');
	E = createNode('E');

	insert(&root, root, A);
	insert(&root, A, B);
	insert(&root, A, C);
	insert(&root, B, D);
	insert(&root, B, E);

	printf("creating a binary tree\n\nthree binary tree traversals\n");
	printf("inorder traversal     : ");
	inorder(root);
	printf("\npreorder traversal    : ");
	preorder(root);
	printf("\npostorder traversal   : ");
	postorder(root);
	printf("\n");

	return 0;
}

void insert(treePointer *first, treePointer frontnode, treePointer newnode) {
	if (!(*first)) {
		newnode->leftChild = NULL;
		newnode->rightChild = NULL;
		*first = newnode;
	}
	else {
		if (frontnode->leftChild == NULL) {
			frontnode->leftChild = newnode;
			newnode->leftChild = NULL;
			newnode->rightChild = NULL;
		}
		else if (frontnode->rightChild == NULL) {
			frontnode->rightChild = newnode;
			newnode->leftChild = NULL;
			newnode->rightChild = NULL;
		}
	}
}
treePointer createNode(char A) {
	treePointer temp;
	temp = (tNode *)malloc(sizeof(tNode));
	temp->data = A;
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