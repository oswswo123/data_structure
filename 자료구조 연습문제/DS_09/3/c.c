#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct polyNode *polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;
polyPointer A, B;

polyPointer lastA, lastB, avail = NULL;

polyPointer cpadd(polyPointer a, polyPointer b);
void printCList(polyPointer first);
void cerase(polyPointer *first);
void erase();
polyPointer getNode();
void attach(int coefficient, int exponent, polyPointer *ptr);
int compare(int a, int b);
void insertFront(polyPointer first, int coef_data, int expon_data);
void insertLast(polyPointer *last, int coef_data, int expon_eata);


int main()
{
	A = getNode();
	B = getNode();
	A->expon = -1;
	B->expon = -1;
	A->link = A;
	B->link = B;
	lastA = A;
	lastB = B;

	FILE *f1;

	char inputtype;
	int coef = 0, expon = 0;

	fopen_s(&f1, "a.txt", "r");
	fscanf_s(f1, "%c", &inputtype);
	switch (inputtype) {
	case 'a':
		fscanf_s(f1, "%d %d", &coef, &expon);
		insertLast(&lastA, coef, expon);
		while (!feof(f1)) {
			fscanf_s(f1, "%d %d", &coef, &expon);
			insertFront(A, coef, expon);
		}
	case 'd':
		while (!feof(f1)) {
			fscanf_s(f1, "%d %d", &coef, &expon);
			insertLast(&lastA, coef, expon);
		}
	}
	fclose(f1);

	fopen_s(&f1, "b.txt", "r");
	fscanf_s(f1, "%c", &inputtype);
	switch (inputtype) {
	case 'a':
		fscanf_s(f1, "%d %d", &coef, &expon);
		insertLast(&lastB, coef, expon);
		while (!feof(f1)) {
			fscanf_s(f1, "%d %d", &coef, &expon);
			insertFront(B, coef, expon);
		}
	case 'd':
		while (!feof(f1)) {
			fscanf_s(f1, "%d %d", &coef, &expon);
			insertLast(&lastB, coef, expon);
		}
	}
	fclose(f1);
	
	printf("     a : ");
	printCList(A);
	printf("     b : ");
	printCList(B);
	printf(" a+b=c : ");
	polyPointer C = cpadd(A, B);
	printCList(C);
	cerase(&A);
	cerase(&B);
	cerase(&C);
	erase();

	return 0;
}

void insertFront(polyPointer first, int coef_data, int expon_data) {
	polyPointer temp;
	temp = getNode();
	temp->coef = coef_data;
	temp->expon = expon_data;
	temp->link = first->link;
	first->link = temp;
}

void insertLast(polyPointer *last, int coef_data, int expon_data) {
	polyPointer temp;
	temp = getNode();
	temp->coef = coef_data;
	temp->expon = expon_data;
	temp->link = (*last)->link;
	(*last)->link = temp;
	*last = temp;
}
polyPointer cpadd(polyPointer a, polyPointer b){
	polyPointer startA, c, lastC;
	int sum, done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1;
	lastC = c;
	do {
		switch (compare(a->expon, b->expon)) {
		case -1:	// a < b
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0:		// a == b
			if (startA == a) done = TRUE;
			else {
				sum = a->coef + b->coef;
				if (sum) attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
			break;
		case 1:		// a > b
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}
void printCList(polyPointer first) {
	polyPointer startF;
	startF = first;
	for (first = first->link; first != startF; first = first->link) {
		if(first->coef > 0)
			printf("+%dx^%d  ", first->coef, first->expon);
		else
			printf("%dx^%d  ", first->coef, first->expon);
	}
	printf("\n");
}
void cerase(polyPointer *first) {
	polyPointer temp;
	if (*first) {
		temp = (*first)->link;
		(*first)->link = avail;
		avail = temp;
		(*first) = NULL;
	}
}
void erase() {
	polyPointer curr;
	while (avail) {
		curr = avail->link;
		free(avail);
		avail = curr;
	}
}
polyPointer getNode() {
	polyPointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else
		node = (polyNode *)malloc(sizeof(polyNode));
	return node;
}
void attach(int coefficient, int exponent, polyPointer *ptr) {
	polyPointer temp;
	temp = (polyNode *)malloc(sizeof(polyNode));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	(*ptr) = temp;
}
int compare(int a, int b) {
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}