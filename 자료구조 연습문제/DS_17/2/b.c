#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000

int vertex = 0;
int weight[MAX_VERTICES][MAX_VERTICES];
int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

int get_min_vertex(int n);
void prim(int s, int n);

int main()
{
	FILE *fp;
	int edge, ipu, ipv, ipkey, buffer;

	fopen_s(&fp, "input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(fp, "%d ", &edge);
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}

	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d", &ipu, &ipv, &ipkey);
		weight[ipu][ipv] = ipkey;
		weight[ipv][ipu] = ipkey;

		if (ipu < ipv)	buffer = ipv;
		else			buffer = ipu;

		if (vertex < buffer) vertex = buffer;
	}

	prim(0, vertex+1);

	return 0;
}

int get_min_vertex(int n) {

	int v, i;
	for (i = 0; i<n; i++)
		if (!selected[i]) {		// ���� �տ��ִ� ���þȵ� vertex
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (dist[i] < dist[v])) // �װ� ���� ª��?
			v = i;

	
	return v;

}
void prim(int s, int n) {
	int i, u, v, cost = 0;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}

	dist[s] = 0;
	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		printf("���� vertex : %d  distance : ", u);
		for (v = 0; v < n; v++)
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v]) // ���� �ٲ�������
					dist[v] = weight[u][v];
		for (int j = 0; j < n; j++) {
			if (dist[j] == INF)
				printf("  INF");
			else
				printf("%5d", dist[j]);
		}
		printf("\n");
		cost += dist[u];
	}
	printf("�ּҺ�� : %d\n", cost);
}