#define SWAP(x,y,t) {t = x; x = y; y = t;}

typedef struct element {
	int key;
	char name[10];
	int grade;
}element;

void selection_sort(element list[], int n) {
	int i, j, least;
	element temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j].key < list[least].key)
				least = j;
		SWAP(list[i], list[least], temp);
	}
}
void bubble_sort(element list[], int n) {
	int i, j, counter = 1;
	element temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			if (list[j].key > list[j + 1].key) {
				SWAP(list[j], list[j + 1], temp);
			}
		printf("<<<<<<<<<< Step %d : Sorted List >>>>>>>>>>\n", counter++);
		for (int k = 0; k < n; k++)
			printf("( %2d, %s, %2d)\n", list[k].key, list[k].name, list[k].grade);
		printf("\n");
	}
}