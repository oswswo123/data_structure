#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

int compare(int a, int b);
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD);
void attach(float coefficient, int exponent);
void poly_print(char a, int start, int finish);

struct term {
	float coef;
	int expon;
}typedef term;
term terms[MAX_TERMS];
int avail = 0;

int main()
{
	int startA = 0, startB, finishA, finishB, startD, finishD;
	int numA, numB;
	printf("<< D(x) = A(x) + B(x) >>\n");

	printf("Input the number of items of A(x) : ");  // input the each element's number
	scanf_s("%d", &numA);
	printf("Input the number of items of B(x) : ");
	scanf_s("%d", &numB);
	finishA = numA - 1;
	startB = numA;
	finishB = numA + numB - 1;
	avail = numA + numB;

	printf("\ninput in descending order\n");
	printf("\ncoefficient and exponent of A(x)=10x^3+8x^2+3 (10 3, 8 2, 3 0) : ");
	for (int i = 0; i < numA; i++)
		scanf_s("%f %d,", &terms[i].coef, &terms[i].expon);
	printf("coefficient and exponent of B(x)=10x^3+8x^2+3(10 3, 8 2, 3 0) : ");
	for (int i = 0; i < numB; i++)
		scanf_s("%f %d,", &terms[startB + i].coef, &terms[startB + i].expon);

	padd(startA, finishA, startB, finishB, &startD, &finishD);

	poly_print('A', startA, finishA);
	poly_print('B', startB, finishB);
	poly_print('D', startD, finishD);

	return 0;
}

int compare(int a, int b) 
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD)
{
	float coefficient;
	*startD = avail;

	while (startA <= finishA && startB <= finishB)
		switch (compare(terms[startA].expon, terms[startB].expon)) {
		case -1:  // a expon < b expon
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
			break;
		case 0:  // equal exxponets
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;
		case 1: // a expon > b expon
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
		}
	for (; startA <= finishA; startA++)     // add in remaining terms of A(x)
		attach(terms[startA].coef, terms[startA].expon);
	for (; startB <= finishB; startB++)     // add in remaining terms of B(x)
		attach(terms[startB].coef, terms[startB].expon);
	*finishD = avail - 1;
}
void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polyniomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}
void poly_print(char a, int start, int finish)
{
	printf("%c(x) = ", a);
	for (;start < finish; start++)
		printf("%.0fx^%d + ", terms[start].coef, terms[start].expon);
	if (terms[finish].expon == 0)
		printf("%.0f\n", terms[finish].coef);
	else
		printf("%.0fx^%d\n", terms[finish].coef, terms[finish].expon);
}
