#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE} tBoolean;
typedef struct edge* tEdgePointer;
typedef struct edge {
	tBoolean marked;
	int vertex1;
	int vertex2;
	tEdgePointer link1;
	tEdgePointer link2;
}tEdge;
tEdgePointer *adjMulList;

int vertexnum;
int edgenum;

tEdgePointer createEdge(int ver1, int ver2);
void addEdge(tEdgePointer temp, int ver1, int ver2);
void printMultilist(int numVertex, int choice);

int main()
{
	FILE *fp;
	int ver1, ver2;
	tEdgePointer temp;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file!!\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d %d", &vertexnum, &edgenum);
	adjMulList = (tEdgePointer *)malloc(sizeof(tEdgePointer) * vertexnum);
	for (int i = 0;i < vertexnum; i++)
		adjMulList[i] = NULL;
	while (!feof(fp)) {
		fscanf_s(fp, "%d %d", &ver1, &ver2);
		temp = createEdge(ver1, ver2);
		addEdge(temp, ver1, ver2);
	}

	printf("<<<<<<<<<< edges incident to each vertex >>>>>>>>>>\n\n");
	printf("간선의 정점 출력 순서 - 입력데이터 순서대로\n");
	for (int i = 0; i < vertexnum; i++) {
		printf("edges incident to vertex %d : ", i);
		printMultilist(i, 0);
		printf("\n");
	}
	printf("\n간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
	for (int i = 0; i < vertexnum; i++) {
		printf("edges incident to vertex %d : ", i);
		printMultilist(i, 1);
		printf("\n");
	}

	return 0;
}

tEdgePointer createEdge(int ver1, int ver2) {
	tEdgePointer temp;
	temp = (tEdge *)malloc(sizeof(tEdge));
	temp->marked = TRUE;
	temp->vertex1 = ver1;
	temp->vertex2 = ver2;
	temp->link1 = NULL;
	temp->link2 = NULL;

	return temp;
}
void addEdge(tEdgePointer temp, int ver1, int ver2) {
	tEdgePointer travel;
	if (adjMulList[ver1] == NULL) {
		temp->link1 = NULL;
		adjMulList[ver1] = temp;
	}
	else {
		travel = adjMulList[ver1];
		while (1) {
			if (travel->vertex1 == ver1) {
				if (travel->link1 == NULL) {
					travel->link1 = temp;
					break;
				}
				travel = travel->link1;
			}
			else if (travel->vertex2 == ver1) {
				if (travel->link2 == NULL) {
					travel->link2 = temp;
					break;
				}
				travel = travel->link2;
			}
		}
	}

	if (adjMulList[ver2] == NULL) {
		temp->link2 = NULL;
		adjMulList[ver2] = temp;
	}
	else {
		travel = adjMulList[ver2];
		while (1) {
			if (travel->vertex1 == ver2) {
				if (travel->link1 == NULL) {
					travel->link1 = temp;
					break;
				}
				travel = travel->link1;
			}
			else if (travel->vertex2 == ver2) {
				if (travel->link2 == NULL) {
					travel->link2 = temp;
					break;
				}
				travel = travel->link2;
			}
		}
	}
}
void printMultilist(int numVertex, int choice) {
	tEdgePointer travel = adjMulList[numVertex];

	if (choice == 0) {
		while (travel) {
			printf("(%d, %d)", travel->vertex1, travel->vertex2);
			if (numVertex == travel->vertex1)
				travel = travel->link1;
			else if (numVertex == travel->vertex2)
				travel = travel->link2;
		}
	}
	else if (choice == 1) {
		while (travel) {
			if (numVertex == travel->vertex1)
				printf("(%d, %d)", travel->vertex1, travel->vertex2);
			else if (numVertex == travel->vertex2)
				printf("(%d, %d)", travel->vertex2, travel->vertex1);

			if (numVertex == travel->vertex1)
				travel = travel->link1;
			else if (numVertex == travel->vertex2)
				travel = travel->link2;
		}
	}
}