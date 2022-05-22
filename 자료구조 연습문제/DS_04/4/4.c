#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING 100
#define MAX_PAT 30

int nfind(char *string, char *pat);

int main()
{
	char *string, *pat;
	int start;
	string = (char *)malloc(MAX_STRING * sizeof(char));
	pat = (char *)malloc(MAX_PAT * sizeof(char));	

	printf("문자열을 입력하세요(MAX : 100) : ");
	scanf_s("%s", string, MAX_STRING);
	printf("비교할 패턴을 입력하세요(MAX : 30) : ");
	scanf_s("%s", pat, MAX_PAT);

	start = nfind(string, pat);
	if (start == -1) {
		fprintf(stderr, "문자열 내에 동일한 패턴이 없습니다.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("문자열 string[%d]번째부터 패턴이 시작됩니다.\n", start);

	free(string);
	free(pat);

	return 0;
}

int nfind(char *string, char *pat) {
	int i = 0, j = 0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++)
				;
		if (j == lastp)
			return start;
	}
	return -1;
}