#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(a,b,c) ( (c) = (a) , (a) = (b) , (b) = (c) )
void sort(int ary[], int size);
int compare(int a, int b);
int binery_search(int ary[], int search_number, int left, int right);

int main()
{
	int size, search_number;
	int a[MAX_SIZE];
	printf("������ ������ �Է��Ͻʽÿ�.(�ִ밪 100) : ");
	scanf_s("%d", &size);
	if (!((size > 0) || (size < MAX_SIZE))) {
		fprintf(stderr, "�ùٸ� �Է°��� �ƴմϴ�.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size; i++) {
		a[i] = rand() % 1000;
		printf("%d ", a[i]);
	}
	sort(a, size);
	printf("\n���� ���� ���� ��\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
	printf("\nã�� ���� �Է��Ͻʽÿ�.(0~999) : ");
	scanf_s("%d", &search_number);
	if (!((search_number > 0) && (search_number < 999))) {
		fprintf(stderr, "�Է°��� �� �� �Ǿ����ϴ�.");
		exit(EXIT_FAILURE);
	}
	if ((binery_search(a, search_number, 0, size-1) == 999)) {
		fprintf(stderr, "�ش� ���� �������� �ʽ��ϴ�.\n");
		exit(EXIT_FAILURE);
	}
	printf("ã�� ���� a[%d]�� �ֽ��ϴ�.\n",binery_search(a, search_number, 0, size-1));

	return 0;
}

void sort(int ary[], int size)
{
	int tmp = 0;
	for (int i = 0; i < size-1; i++) {
		for (int j = i; j < size-1; j++) {
			if (ary[i] > ary[j + 1]) {
				SWAP(ary[i], ary[j + 1], tmp);
			}
		}
	}
}
int compare(int a, int b)
{
	if (a < b)
		return -1;
	else if (a == b) return 0;
	else return 1;
}
int binery_search(int ary[], int search_number, int left, int right)
{
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(ary[middle], search_number)) {
		case -1:
			left = middle + 1;
			break;
		case 0:
			return middle;
		case 1:
			right = middle - 1;
		}
	}
	return 999;
}