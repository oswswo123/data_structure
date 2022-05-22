#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

int **run;
int *winnertree, *sorted, *record;
void makerun(int k);
void makewinnertree(int **winnertree, int k);
int getwinner(int *winnertree, int k);
void inorder(int n, int k);

int main()
{
	int k, seed;
	printf("the number of keys ( 4, 8, 16 or 32 as a power of 2) : ");
	scanf_s("%d", &k);
	printf("value of seed : ");
	scanf_s("%u", &seed);
	srand(seed);

	makerun(k);

	makewinnertree(&winnertree, k);
	
	int winner;
	sorted = (int *)malloc(sizeof(int) * k * 10);

	printf("\n\nsorting with min-winner tree...\n\n");
	for (int i = 0; i < k * 10; i++) {
		winner = getwinner(winnertree, k);
		sorted[i] = winner;
	}

	printf("sorted result\n");
	for (int i = 0; i < k * 10; i++) {
		if (i && i % 10 == 0)
			printf("\n");
		printf("%3d ", sorted[i]);
	}
	printf("\n");

	return 0;
}

void inorder(int n, int k) {
	if (n < (2 * k)) {
		inorder(2 * n, k);
		printf("%3d ", winnertree[n]);
		inorder(2 * n + 1, k);
	}
}
void makerun(int k) {
	run = (int **)malloc(sizeof(int*) * k);

	for (int i = 0; i < k; i++) {
		run[i] = (int *)malloc(sizeof(int) * 10);
		run[i][0] = 1 + rand() % MAX_SIZE;
		for (int j = 1; j < 10; j++)
			run[i][j] = run[i][j - 1] + 1;
	}

	for (int i = 0; i < k; i++) {
		printf("%d-th records:\n", i+1);
		for (int j = 0; j < 10; j++)
			printf(" %3d ", run[i][j]);
		printf("\n");
	}
}
void makewinnertree(int **winnertree, int k) {
	(*winnertree) = (int *)malloc(sizeof(int) * k * 2 - 1);
	(*winnertree)[0] = NULL;
	record = (int *)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++)
		record[i] = 0;

	for (int i = 0; i < k; i++) {
		(*winnertree)[k + i] = run[i][0];
	}

	for (int i = k * 2 - 1; i != 1; i -= 2) {
		if ((*winnertree)[i] >(*winnertree)[i - 1])
			(*winnertree)[i / 2] = (*winnertree)[i - 1];
		else
			(*winnertree)[i / 2] = (*winnertree)[i];
	}
}
int getwinner(int *winnertree, int k) {
	int winner = winnertree[1];
	int i;

	for (i = 0; i < k; i++) {
		if (winnertree[1] == winnertree[k + i]) {
			if (record[i] == 9)
				winnertree[k + i] = 9999;
			else
				winnertree[k + i] = run[i][++record[i]];
			break;
		}
	}
	for (i += k; i != 1; i /= 2) {
		if (winnertree[i/2*2] > winnertree[i/2*2+1])
			winnertree[i / 2] = winnertree[i/2*2+1];
		else
			winnertree[i / 2] = winnertree[i/2*2];
	}

	return winner;
}