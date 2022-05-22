#include <stdio.h>
#include <stdlib.h>
#define MAX 11

typedef struct element *elementPointer;
typedef struct element {
	char item[10];
	int key;
}element;

int b = MAX;
elementPointer *ht;

unsigned int h(int k);
unsigned int stringToInt(char *key);
element* search(int k);
void insertHash(element item, int index);
void printHash();

int main()
{
	FILE *fp;
	int hk;
	char searchvalue[10];
	element buffer;
	ht = malloc(sizeof(elementPointer) * MAX);
	for (int i = 0; i < MAX; i++)
		ht[i] = NULL;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	printf(" input strings : ");
	while(!feof(fp)) {
		fscanf_s(fp, "%s ", buffer.item, 10);
		printf("%s ", buffer.item);
		buffer.key = stringToInt(buffer.item);
		hk = h(buffer.key);
		insertHash(buffer, hk);
	}

	printHash();

	printf("string to search>> ");
	scanf_s("%s", searchvalue, 10);
	hk = stringToInt(searchvalue);
	search(hk);

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
element* search(int k) {
	int homeBucket, currentBucket, counter = 1;
	homeBucket = h(k);
	for (currentBucket = homeBucket; ht[currentBucket]
		&& ht[currentBucket]->key != k;) {
		currentBucket = (currentBucket + 1) % b;
		counter++;
		if (currentBucket == homeBucket)
			return NULL;
	}
	if (ht[currentBucket] == NULL) {
		printf("it dosen't exist!\n");
		return NULL;
	}
	if (ht[currentBucket]->key == k){
		printf("item : %s, key : %d, the number of comparisions : %d\n",
			ht[currentBucket]->item, ht[currentBucket]->key, counter);
		return ht[currentBucket];
	}
	return NULL;
}
void insertHash(element item, int index) {
	while (ht[index] != NULL)
		index++;
	elementPointer temp;
	temp = (element *)malloc(sizeof(element));
	temp->key = item.key;
	strcpy_s(temp->item, 10, item.item);

	ht[index] = temp;
}
void printHash() {
	printf("\n\n             item    key\n");
	for (int i = 0; i < MAX; i++) {
		printf("ht[%2d] :   ", i);
		if (ht[i] == NULL)
			printf("\n");
		else
			printf("%6s %6d\n", ht[i]->item, ht[i]->key);
	}
	printf("\n");
}