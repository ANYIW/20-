#include <stdio.h>
#include <stdlib.h>
#define INF 65536
#define MAX 1001
typedef long long T;

T graph[MAX][MAX];//记录边权
T dist[MAX];//跨边权值
T maxEdge[MAX][MAX];//MST内i到j的最大边
int path[MAX];//跨边中在集合内的点
T goods[MAX];//记录点权
int flag[MAX][MAX];//边是否在MST内

void Initial(int n)
{
	for (int i = 1; i <= n; i++)
	{
		dist[i] = INF;
		goods[i] = 0;
		for (int j = 1; j <= n; j++)
			if (i != j) {
				graph[i][j] = INF;
				flag[i][j] = 0;
			}
	}
}
int ScanMin(int n)
{
	int index = -1;
	T min = INF;
	for (int i = 1; i <= n; i++)
	{
		if (dist[i] != 0 && dist[i] < min)
		{
			index = i;
			min = dist[i];
		}
	}
	return index;
}
T Max(T a, T b) {
	return (a > b) ? a : b;
}
int Prim(int n)
{
	int sum = 0;
	dist[1] = 0;
	for (int i = 1; i <= n; i++)
	{
		if (graph[1][i] != INF)
		{
			dist[i] = graph[1][i];
			path[i] = 1;
		}
	}
	while (1)
	{
		int v = ScanMin(n);
		if (v == -1)
			break;
		int u = path[v];
		maxEdge[v][u] = maxEdge[u][v] = dist[v];
		//dist[v] = 0;
		for (int i = 1; i <= n; i++) {
			if (dist[i] == 0) {
				maxEdge[v][i] = maxEdge[i][v] = Max(maxEdge[u][v], maxEdge[i][u]);
			}
		}
		sum += dist[v];
		flag[u][v] = 1;
		dist[v] = 0;//此时才能将v加入集合
		for (int i = 1; i <= n; i++)
		{
			if (graph[v][i] != INF && dist[i] > graph[v][i])
			{
				dist[i] = graph[v][i];
				path[i] = v;
			}
		}
	}
	return sum;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	Initial(n);
	for (int i = 0; i < n; i++)
		scanf("%lld", &goods[i]);
	while (m--)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (graph[a][b] == INF || graph[a][b] > c) //防止输入重边
			graph[a][b] = graph[b][a] = c;
	}
	int sum = Prim(n);

	T X;
	int Y;
	T max = -1;
	int e, f;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			X = goods[i] + goods[j];
			if (graph[i][j] != INF) {
				if (flag[i][j] == 1) {
					Y = sum - graph[i][j];
				}
				else {
					Y = sum - maxEdge[i][j] + 0;//将ij边权变为0后MST的值
				}
				T tmp = X / Y;
				if (tmp >= max) {
					max = tmp;
					e = i;
					f = j;
				}
			}
		}
	}
	printf("%lld\n", max);
	printf("%d %d\n", e, f);
	return 0;
}
/*
5 7
12834152 18042779 47215528 68501643 17854429
1 3 134
5 2 227
3 2 873
4 3 252
1 5 605
1 2 269
4 1 135

233300
3 2
*/