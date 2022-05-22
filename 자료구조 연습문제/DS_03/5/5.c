#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101


struct {
	int degree;
	float coef[MAX_DEGREE];
} typedef polynomial;

int compare(int a, int b);
void poly_print(char a, polynomial b);

int main()
{
	polynomial A, B, C;
	int repet = 0;

	printf("<< C(x) = A(x) + B(x) >>\n");

	printf("A(x)의 차수 : ");
	scanf_s("%d", &A.degree);
	printf("A(x)의 계수 : ");
	for (int i = 0; i < A.degree + 1; i++)
		scanf_s("%f", &A.coef[i]);
	printf("B(x)의 차수 : ");
	scanf_s("%d", &B.degree);
	printf("B(x)의 계수 : ");
	for (int i = 0; i < B.degree + 1; i++)
		scanf_s("%f", &B.coef[i]);
	
	if (A.degree > B.degree)
		C.degree = A.degree;
	else if (A.degree < B.degree)
		C.degree = B.degree;
	else
		C.degree = A.degree;

	switch (compare(A.degree, B.degree)) {
	case 0:		// a == b
		for (int i = 0; i < (C.degree + 1); i++)
			C.coef[i] = A.coef[i] + B.coef[i];
		break;
	case 1:		// a < b
		for (; A.degree < B.degree - repet; repet++)
			C.coef[repet] = B.coef[repet];
		for (int i = 0; i < (C.degree + 1 - repet); i++)
			C.coef[repet + i] = B.coef[repet + i] + A.coef[i];
		break;
	case -1:	// a > b
		for (; B.degree < A.degree - repet; repet++)
			C.coef[repet] = A.coef[repet];
		for (int i = 0; i < (C.degree + 1 - repet); i++)
			C.coef[repet + i] = A.coef[repet + i] + B.coef[i];
		break;
	}
	
	poly_print('A', A);
	poly_print('B', B);
	poly_print('C', C);

	return 0;
}

int compare(int a, int b)
{
	if (a < b)
		return 1;
	else if (a > b)
		return -1;
	else
		return 0;
}
void poly_print(char a, polynomial b)
{
	printf("%c(x) = ", a);
	for (int i = 0; i < b.degree; i++) {
		printf("%.0fx^%d + ", b.coef[i], b.degree - i);
	}
	printf("%.0f\n", b.coef[b.degree]);
}