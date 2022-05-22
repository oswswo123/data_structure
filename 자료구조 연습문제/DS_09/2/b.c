#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polyNode *polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;
polyPointer A, B;

polyPointer findLast(polyPointer first);
void inputPoly(polyPointer first, FILE *f);
void insert(polyPointer x, int coef_data, int expon_data);
void printList(polyPointer first);
int compare(int a, int b);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer *ptr);
void erase(polyPointer *ptr);

int main()
{
	A = (polyNode *)malloc(sizeof(polyNode));
	B = (polyNode *)malloc(sizeof(polyNode));
	A->link = NULL;
	B->link = NULL;

	FILE *f1;

	fopen_s(&f1, "a.txt", "r");
	inputPoly(A, f1);
	fclose(f1);

	fopen_s(&f1, "b.txt", "r");
	inputPoly(B, f1);
	fclose(f1);
	
	A = A->link;
	B = B->link;
	polyPointer C = padd(A, B);
	printf("     a : ");
	printList(A);
	printf("     b : ");
	printList(B);
	printf(" a+b=c : ");
	printList(C);

	erase(&A);
	erase(&B);
	erase(&C);

	return 0;
}

polyPointer findLast(polyPointer first) {
	polyPointer curr;
	curr = first;
	while (first) {
		curr = first;
		first = first->link;
	}
	return curr;
}
void inputPoly(polyPointer first, FILE *f) {
	char inputtype;
	int coef = 0, expon = 0;
	polyPointer finder;

	fscanf_s(f, "%c", &inputtype);
	switch (inputtype) {
	case 'a':
		while (!feof(f)) {
			fscanf_s(f, "%d %d", &coef, &expon);
			insert(first, coef, expon);
		}
		break;
	case 'd':
		while (!feof(f)) {
			fscanf_s(f, "%d %d", &coef, &expon);
			finder = findLast(first);
			insert(finder, coef, expon);
		}
	}
}
void insert(polyPointer x, int coef_data, int expon_data) {
	polyPointer temp;
	temp = (polyNode *)malloc(sizeof(polyNode));
	temp->coef = coef_data;
	temp->expon = expon_data;
	temp->link = x->link;
	x->link = temp;
}
void printList(polyPointer first) {
	for (; first; first = first->link) {
		if (first->coef > 0)
			printf("+%dx^%d  ", first->coef, first->expon);
		else
			printf("%dx^%d  ", first->coef, first->expon);
	}
	printf("\n");
}
polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;
	rear = (polyNode *)malloc(sizeof(polyNode));
	c = rear;
	while (a && b) {
		switch (compare(a->expon, b->expon)) {
		case -1:	// a < b
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:		// a == b
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1:		// a > b
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);
	return c;
}
	
int compare(int a, int b) {
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
void attach(int coefficient, int exponent, polyPointer *ptr) {
	polyPointer temp;
	temp = (polyNode *)malloc(sizeof(polyNode));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}
void erase(polyPointer *ptr) {
	polyPointer temp;
	while (*ptr) {
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}
