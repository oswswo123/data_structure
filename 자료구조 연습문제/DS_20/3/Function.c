#define SWAP(x,y,temp) {temp = x; x = y; y = temp;}

typedef struct element {
	int key;
	int link;
}element;

void merge(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].key <= initList[j].key)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}
void mergedPass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];
}
void mergeSort(element a[], int n) {
	int s = 1;
	element extra[100];

	while (s < n) {
		mergedPass(a, extra, n, s);
		s *= 2;
		mergedPass(extra, a, n, s);
		s *= 2;
	}
}
int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;)
		if (a[last1].key <= a[last2].key) {
			a[lastResult].link = last1;
			lastResult = last1;
			last1 = a[last1].link;
		}
		else {
			a[lastResult].link = last2;
			lastResult = last2;
			last2 = a[last2].link;
		}
		if (last1 == 0)
			a[lastResult].link = last2;
		else
			a[lastResult].link = last1;
		return a[0].link;
}
int rmergeSort(element a[], int link[], int left, int right) {
	int mid;
	if (left >= right) return left;
	mid = (left + right) / 2;
	return listMerge(a, link,
		rmergeSort(a, link, left, mid),
		rmergeSort(a, link, mid + 1, right));
}
void adjust_(element a[], int root, int n) {
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && (a[child].key < a[child + 1].key))
			child++;
		if (rootkey > a[child].key)
			break;
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}
void heapSort(element a[], int n) {
	int i, counter = 1;
	element temp;

	for (i = n / 2; i > 0; i--)
		adjust_(a, i, n);

	printf("after initialization of max heap...\n");
	for (i = 1; i < n+1; i++)
		printf("%3d ", a[i]);
	printf("\n\n\n");

	for (i = n - 1; i > 0; i--) {
		printf("step %2d : ", counter++);
		printf("Ãâ·Â %2d : ", a[1]);
		SWAP(a[1], a[i + 1], temp);
		adjust_(a, 1, i);
		for (int j = 1; j < n + 2 - counter; j++)
			printf("%3d ", a[j]);
		printf("\n");
	}
}