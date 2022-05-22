#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

struct offsets {
	short int vert;
	short int horiz;
}typedef offsets;
struct element {
	short int row;
	short int col;
	short int dir;
}typedef element;

element stack[MAX_STACK_SIZE];
offsets move[8];
int top = -1;
int EXIT_ROW, EXIT_COL;

void path(void);
void push(element item);
element pop();
void stackFull();
element stackEmpty();
int mark[10][10] = { 0 };
int maze[10][10] = { 0 };

int main()
{
	FILE *f1;
	fopen_s(&f1, "input.txt", "r");
	fscanf_s(f1, "%d %d\n", &EXIT_ROW, &EXIT_COL);
	for (int i = 1; i <= EXIT_ROW; i++) {
		for (int j = 1; j <= EXIT_COL; j++) 
			fscanf_s(f1, " %d", &maze[i][j]);
	}
	for (int i = 0; i <= EXIT_COL + 1; i++) {
		maze[0][i] = 1;
		maze[EXIT_ROW + 1][i] = 1;
	}
	for (int i = 0; i <= EXIT_ROW; i++) {
		maze[i][0] = 1;
		maze[i][EXIT_COL + 1] = 1;
	}

	
	move[0].vert = -1;	move[0].horiz = 0;
	move[1].vert = -1;	move[1].horiz = 1;
	move[2].vert = 0;	move[2].horiz = 1;
	move[3].vert = 1;	move[3].horiz = 1;
	move[4].vert = 1;	move[4].horiz = 0;
	move[5].vert = 1;	move[5].horiz = -1;
	move[6].vert = 0;	move[6].horiz = -1;
	move[7].vert = -1;	move[7].horiz = -1;

	path();
	for (int i = 1; i < EXIT_ROW + 1; i++) {
		for (int j = 1; j < EXIT_COL + 1; j++)
			printf("%2d ", maze[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i = 1; i < EXIT_ROW + 1; i++) {
		for (int j = 1; j < EXIT_COL + 1; j++)
			printf("%2d ", mark[i][j]);
		printf("\n");
	}

	return 0;
}

void path(void) {
	int row, col, nextRow = 0, nextCol = 0, dir, found = FALSE;
	element position;
	mark[1][1] = 1;		top = 0;
	stack[0].row = 1;	stack[0].col = 1;	stack[0].dir = 1;

	while (top > -1 && !found) {
		position = pop();
		row = position.row;		col = position.col;		dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row;		position.col = col;		position.dir = ++dir;
				push(position);
				row = nextRow;		col = nextCol;		dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path is :\n");
		printf("row  col\n");
		for (int i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n\n", EXIT_ROW, EXIT_COL);
	}
	else {
		fprintf(stderr, "The maze does not have a path!\n");
		exit(EXIT_FAILURE);
	}
}
void push(element item) {
	top++;
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	else
		stack[top] = item;
}
element pop() {
	if (top > -1)
		return stack[top--];
	else
		stackEmpty();
}
void stackFull() {
	fprintf(stderr, "Stack is Full! This stack can't push!\n");
	exit(EXIT_FAILURE);
}
element stackEmpty() {
	fprintf(stderr, "Stack is Empty! This stack can't pop!\n");
	exit(EXIT_FAILURE);
}