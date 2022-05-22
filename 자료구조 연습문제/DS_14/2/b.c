#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

int *run, *winnertree, *sorted;
void makerun(int **run, int k);
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

	makerun(&run, k);
	makewinnertree(&winnertree, k);

	printf("\nInorder traversal for min-winner tree\n");
	inorder(1, k);
	printf("\nWinner Tree Inorder traversal after find 2 winners\n");

	int winner;
	sorted = (int *)malloc(sizeof(int) * k);
	for (int i = 0; i < 2; i++) {
		winner = getwinner(winnertree, k);
		sorted[i] = winner;
	}
	inorder(1, k);

	printf("\n\nsorting with min-winner tree...\n\n");
	for (int i = 2; i < k; i++) {
		winner = getwinner(winnertree, k);
		sorted[i] = winner;
	}

	printf("sorted result\n");
	for (int i = 0; i < k; i++)
		printf("%3d ", sorted[i]);
	printf("\n");

	free(run);
	free(sorted);
	
	return 0;
}

void inorder(int n, int k) {
	if (n < (2 * k)) {
		inorder(2 * n, k);
		printf("%3d ", winnertree[n]);
		inorder(2 * n + 1, k);
	}
}
void makerun(int **run, int k) {
	(*run) = (int *)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) {		// ignore index 0
		(*run)[i] = 1 + rand() % MAX_SIZE;
		printf("%3d ", (*run)[i]);
	}
	printf("\n");
}
void makewinnertree(int **winnertree, int k) {
	(*winnertree) = (int *)malloc(sizeof(int) * k * 2 - 1);
	(*winnertree)[0] = NULL;
	printf("\ninitalization of min-winner tree\n");
	for (int i = 0; i < k; i++) {
		(*winnertree)[k + i] = run[i];
	}

	for (int i = k * 2 - 1; i != 1; i -= 2) {
		if ((*winnertree)[i] > (*winnertree)[i - 1])
			(*winnertree)[i / 2] = (*winnertree)[i - 1];
		else
			(*winnertree)[i / 2] = (*winnertree)[i];
	}
}
int getwinner(int *winnertree, int k) {
	int winner = winnertree[1];

	for (int i = 0; i < k; i++) {
		if (winnertree[1] == winnertree[k + i]) {
			winnertree[k + i] = 9999;
			break;
		}
	}
	for (int i = k * 2 - 1; i != 1; i -= 2) {
		if (winnertree[i] > winnertree[i - 1])
			winnertree[i / 2] = winnertree[i - 1];
		else
			winnertree[i / 2] = winnertree[i];
	}

	return winner;
}