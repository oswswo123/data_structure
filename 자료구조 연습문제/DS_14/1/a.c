#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

typedef int iType;
typedef struct {
	int key;
	iType item;
}element;

typedef struct node *treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
}tNode;

treePointer root;
element* key;

element* search(treePointer first, int key);
element* iterSearch(treePointer first, int k);
void insert(treePointer *first, int k, iType theItem);
treePointer modifiedSearch(treePointer first, int k);
void inorder(treePointer first);

int main()
{
	int n, seed;
	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("the number of nodes in BST (less than and equal to 50) : ");
	scanf_s("%d", &n);
	printf("seed : ");
	scanf_s("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);

	printf("generating number : ");
	key = (element *)malloc(sizeof(element) * n);
	for (int i = 0; i < n; i++) {
		key[i].key = 1 + rand() % MAX_SIZE;
		for (int j = 0; j < i; j++) {
			if (key[j].key == key[i].key) {
				key[i].key = 1 + rand() % MAX_SIZE;
				j = 0;
			}
		}
		key[i].item = key[i].key;
		printf("%3d ", key[i].key);
	}
	
	for (int i = 0; i < n; i++) {
		insert(&root, key[i].key, key[i].item);
	}
	printf("\n");

	printf("the key to search : ");
	int searchnum;
	scanf_s("%d", &searchnum);
	printf("the search process : ");
	search(root, searchnum);

	printf("\ninorder traversal of the BST shows the sorted sequence\n");
	inorder(root);
	printf("\n");

	return 0;
}

element* search(treePointer first, int key) {
	if (!first) return NULL;
	printf("%d => ", first->data.key);
	if (key == first->data.key) {
		printf("\nthe element is BST\n");
		return &(first->data);
	}
	if (key < first->data.key)
		return search(first->leftChild, key);
	return search(first->rightChild, key);
}
element* iterSearch(treePointer first, int k) {
	while (first) {
		if (k == first->data.key) return &(first->data);
		if (k < first->data.key)
			first = first->leftChild;
		else
			first = first->rightChild;
	}
	return NULL;
}
void insert(treePointer *first, int k, iType theItem) {
	treePointer ptr, temp = modifiedSearch(*first, k);
	if (temp || !(*first)) {
		ptr = (tNode *)malloc(sizeof(tNode));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*first)
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		else
			*first = ptr;
	}
}
treePointer modifiedSearch(treePointer first, int k) {
	treePointer temp;
	temp = first;
	if (first == NULL)
		return NULL;
	while (first) {
		if (k == (first)->data.key) return NULL;
		if (k < (first)->data.key) {
			temp = (first);
			(first) = (first)->leftChild;
		}
		else {
			temp = (first);
			(first) = (first)->rightChild;
		}
	}
	return temp;
}
void inorder(treePointer first) {
	if (first) {
		inorder(first->leftChild);
		printf("%3d ", first->data.key);
		inorder(first->rightChild);
	}
}