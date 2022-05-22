#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 80
#define MAX_STRING_SIZE 80

int stack[MAX_STACK_SIZE];
char expr[MAX_STRING_SIZE];
int top = -1;

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

int eval();
precedence getToken(char *symbol, int *n);
void push(int num);
int pop();
void stackFull();
int stackEmpty();

int main()
{
	FILE *f1;
	fopen_s(&f1, "input.txt", "r");
	if (f1 == NULL) {
		fprintf(stderr, "Can't open file!\n");
		exit(EXIT_FAILURE);
	}
	fscanf_s(f1, "%s", expr, MAX_STRING_SIZE);
	
	printf("postfix expression : %s\nthe evaluation value : %d\n", expr, eval());
	
	fclose(f1);
	return 0;
}

int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0'); // 나중에 atoi로도 해보자.
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus: push(op1 + op2);		break;
			case minus: push(op1 - op2);	break;
			case times: push(op1 * op2);	break;
			case divide: push(op1 / op2);	break;
			case mod: push(op1 % op2);		break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
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
void push(int num) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = num;
}
int pop() {
	if (top <= -1)
		stackEmpty();
	return stack[top--];
}
void stackFull() {
	fprintf(stderr, "Stack is Full! can't push this stack!\n");
	exit(EXIT_FAILURE);
}
int stackEmpty() {
	fprintf(stderr, "Stack is Empty! can't pop this stack!\n");
	exit(EXIT_FAILURE);
}