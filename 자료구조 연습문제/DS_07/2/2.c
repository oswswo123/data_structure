#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 80
#define MAX_STRING_SIZE 80

typedef enum { 
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13 ,13, 0 };

precedence stack[MAX_STACK_SIZE];
char expr[MAX_STRING_SIZE];
char post[MAX_STRING_SIZE];
int top = -1;
int posttop = -1;

void postfix();
precedence getToken(char *symbol, int *n);
void push(precedence oper);
precedence pop();
void stackFull();
precedence stackEmpty();
void printToken(precedence oper);

int main()
{
	FILE *f1, *f2;
	fopen_s(&f1, "input.txt", "r");
	fopen_s(&f2, "output.txt", "w");
	fscanf_s(f1, "%s", expr, MAX_STRING_SIZE);
	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("infix expression\t : %s\n", expr);
	printf("postfix expression\t : ");
	postfix();
	fprintf(f2, "%s", post);

	fclose(f1);
	fclose(f2);
	return 0;
}

void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			printf("%c", symbol);
			post[++posttop] = symbol;
		}
		else if (token == rparen) {
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
precedence getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
void push(precedence oper) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = oper;
}
precedence pop() {
	if (top <= -1)
		stackEmpty();
	return stack[top--];
}
void stackFull() {
	fprintf(stderr, "Stack is Full! can't push this stack!\n");
	exit(EXIT_FAILURE);
}
precedence stackEmpty() {
	fprintf(stderr, "Stack is Empty! can't pop this stack!\n");
	exit(EXIT_FAILURE);
}
void printToken(precedence oper) {
	switch (oper) {
	case lparen:printf("("); break;
	case rparen:printf(")"); break;
	case plus:	printf("+"); post[++posttop] = '+'; break;
	case minus:	printf("-"); post[++posttop] = '-'; break;
	case divide:printf("/"); post[++posttop] = '/'; break;
	case times:	printf("*"); post[++posttop] = '*'; break;
	case mod:	printf("%"); post[++posttop] = '%'; break;
	default: break;
	}
}