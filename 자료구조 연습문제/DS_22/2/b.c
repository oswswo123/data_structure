#include <stdio.h>
#include <stdlib.h>
#define MAX 8

typedef struct element* elementPointer;
typedef struct element {
	int key;
}element;

elementPointer *ht;
int b = 8;
int *randNum;

unsigned int h(int k);
element* search(int k);
void insertHash(element item, int index);
void printHash();
void setRand();

int main()
{
	FILE *fp;
	element input;
	int searchNumber = 1;
	ht = (elementPointer *)malloc(sizeof(elementPointer) * b);
	for (int i = 0; i < b; i++)
		ht[i] = NULL;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	printf("key sequence from file : ");
	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &input.key);
		printf("%3d ", input.key);
	}
	fclose(fp);
	printf("\n");

	setRand();

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp)) {
		fscanf_s(fp, "%d ", &input.key);
		insertHash(input, h(input.key));
	}
	fclose(fp);
	printf("\n");

	printHash();

	while (searchNumber) {
		printf("Input 0 to quit\nkey to search >> ");
		scanf_s("%d", &searchNumber);
		if (searchNumber == 0) continue;
		search(searchNumber);
	}

	return 0;
}

unsigned int h(int k) {
	int number;
	number = k % b;
	return number;
}
element* search(int k) {
	int homeBucket, currentBucket, counter = 1, i = 1;
	homeBucket = h(k);
	for (currentBucket = homeBucket; ht[currentBucket]
		&& ht[currentBucket]->key != k;) {
		currentBucket = (currentBucket + randNum[i]) % b;
		i = (i + 1) % b;
		counter++;
		if (currentBucket == homeBucket)
			return NULL;
	}
	if (ht[currentBucket] == NULL) {
		printf("it dosen't exist!\n\n");
		return NULL;
	}
	if (ht[currentBucket]->key == k) {
		printf("key : %d, the number of comparisions : %d\n\n",
			ht[currentBucket]->key, counter);
		return ht[currentBucket];
	}
	return NULL;
}
void insertHash(element item, int index) {
	int i = 1;
	int firstIndex = index;
	while (ht[index] != NULL) {
		if (item.key == ht[index]->key) {
			fprintf(stderr, "\nht is collision.\n");
			exit(EXIT_FAILURE);
		}
		index = (index + randNum[i]) % b;
		i = (i + 1) % b;
		if (firstIndex == index) {
			fprintf(stderr, "\nht is full.\n");
			exit(EXIT_FAILURE);
		}
	}
	elementPointer temp;
	temp = (element *)malloc(sizeof(element));
	temp->key = item.key;

	ht[index] = temp;
}
void printHash() {
	printf("\n              key\n");
	for (int i = 0; i < MAX; i++) {
		printf("ht[%2d] :   ", i);
		if (ht[i] == NULL)
			printf("\n");
		else
			printf("%6d\n", ht[i]->key);
	}
	printf("\n");
}
void setRand() {
	int seed;

	printf("input seed >> ");
	scanf_s("%d", &seed);
	printf("\n");
	srand(seed);
	randNum = (int *)malloc(sizeof(int) * b);
	for (int i = 1; i < b; i++) {
		randNum[i] = rand() % b;
		for (int j = 1; j < i; j++)
			if (randNum[j] == randNum[i] || randNum[i] == 0) {
				randNum[i] = rand() % b;
				j = 0;
			}
	}

	for (int i = 1; i < b; i++)
		printf("randNum[%d] : %2d\n", i, randNum[i]);
}