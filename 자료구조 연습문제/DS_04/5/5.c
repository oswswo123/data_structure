#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING 100
#define MAX_PAT 30

void fail(char *pat);
int pmatch(char *string, char *pat);
int failure[MAX_PAT];
char string[MAX_STRING];
char pat[MAX_PAT];

int main()
{
	int start;

	printf("문자열을 입력하세요(MAX : 100) : ");
	scanf_s("%s", string, MAX_STRING);
	printf("비교할 패턴을 입력하세요(MAX : 30) : ");
	scanf_s("%s", pat, MAX_PAT);
	fail(pat);
	start = pmatch(string, pat);

	if (start == -1) {
		fprintf(stderr, "문자열 내에 동일한 패턴이 없습니다.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < strlen(pat); i++)
		printf("failure[%d] = %d\n", i, failure[i]);
	printf("문자열 string[%d]번째부터 패턴이 시작됩니다.\n", start);
	
	return 0;
}

int pmatch(char *string, char *pat){
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++;
			j++;
		}
		else if (j == 0)
			i++;
		else
			j = failure[j - 1] + 1;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}
void fail(char *pat) {
	int i = 0, j = 0;
	int n = strlen(pat);
	failure[0] = -1;
	for (j = 1;j < n;j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else
			failure[j] = -1;
	}
}