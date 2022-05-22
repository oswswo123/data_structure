typedef struct element {
	int key;
	int link;
}element;

void merge(element initList[], element mergedList[], int i, int m, int n);
void mergedPass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);
int listMerge(element a[], int link[], int start1, int start2);
int rmergeSort(element a[], int link[], int left, int right);
void adjust_(element a[], int root, int n);
void heapSort(element a[], int n);

