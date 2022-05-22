void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void sort(int a[], int b)
{
	for (int i = 0; i < b - 1; i++) {
		for (int j = i+1; j < b; j++) {
			if (a[j] < a[i]) {
				swap(&a[i], &a[j]);
			}
		}
	}
}