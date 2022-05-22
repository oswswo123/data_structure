#include <stdio.h>
#include <stdlib.h>
#define MAX 11

typedef struct element *elementPointer;
typedef struct element {
	char item[10];
	int key;
}element;

typedef struct node *nodePointer;
typedef struct node {
	element data;
	nodePointer link;
}node;

int b = MAX;
nodePointer *ht;

unsigned int h(int k);
unsigned int stringToInt(char *key);
nodePointer search(int k);
void insertHash(element item, int index);
void printHash();

int main()
{
	FILE *fp;
	int hk;
	char searchvalue[10];
	element buffer;
	ht = malloc(sizeof(node) * MAX);
	for (int i = 0; i < MAX; i++)
		ht[i] = NULL;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	printf(" input strings : ");
	while (!feof(fp)) {
		fscanf_s(fp, "%s ", buffer.item, 10);
		printf("%s ", buffer.item);
		buffer.key = stringToInt(buffer.item);
		hk = h(buffer.key);
		insertHash(buffer, hk);
	}

	printHash();

	for (;;) {
		printf("input \"quit\" to quit\nstring to search>> ");
		scanf_s("%s", searchvalue, 10);
		if (strcmp(searchvalue, "quit") == 0)
			break;
		else {
			hk = stringToInt(searchvalue);
			search(hk);
			printf("\n");
		}
	}

	return 0;
}

unsigned int h(int k) {
	int number;
	number = k % b;
	return number;
}
unsigned int stringToInt(char *key) {
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}
nodePointer search(int k) {
	nodePointer temp = ht[h(k)];

	int counter = 1;
	for (; temp && temp->data.key != k;) {
		temp = temp->link;
		counter++;
	}
	if (temp == NULL) {
		printf("it dosen't exist!\n");
		return NULL;
	}
	if (temp->data.key == k) {
		printf("item : %s, key : %d, the number of comparisions : %d\n",
			temp->data.item, temp->data.key, counter);
		return temp;
	}
	return NULL;
}
void insertHash(element item, int index) {
	nodePointer temp;
	temp = (node *)malloc(sizeof(node));
	temp->data = item;
	temp->link = NULL;

	if (ht[index] == NULL) {
		ht[index] = temp;
	}
	else {
		nodePointer srrund;
		srrund = ht[index];
		while (srrund->link != NULL)
			srrund = srrund->link;
		srrund->link = temp;
	}
}
void printHash() {
	printf("\n\n             item    key\n");
	for (int i = 0; i < MAX; i++) {
		printf("ht[%2d] :   ", i);
		if (ht[i] == NULL)
			printf("\n");
		else {
			nodePointer temp;
			temp = ht[i];
			for (; temp; temp = temp->link)
				printf("(%s %d) ", temp->data.item, temp->data.key);
			printf("\n");
		}
	}
	printf("\n");
}