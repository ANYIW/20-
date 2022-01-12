#include <stdio.h>
#include <stdlib.h>
#define INF 65536
#define MAX 2001
typedef long long T;

T graph[MAX][MAX];
T dist[MAX];
T maxEdge[MAX][MAX]; //MST中i到j
int path[MAX];

void Initial(int n)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
        for (int j = 1; j <= n; j++)
            if (i != j)
                graph[i][j] = INF;
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
T Max(T a, T b)
{
    return (a > b) ? a : b;
}
void Prim(int n)
{
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
        int u = path[v];                         //u：跨边在集合中的端点
        maxEdge[v][u] = maxEdge[u][v] = dist[v]; //MST中v到u的最大边
        //dist[v] = 0;
        for (int i = 1; i <= n; i++)
        {
            if (dist[i] == 0)
            { //确保i在集合中
                maxEdge[v][i] = maxEdge[i][v] = Max(maxEdge[u][v], maxEdge[i][u]);
            }
        }
        dist[v] = 0; //后加入！！！
        for (int i = 1; i <= n; i++)
        {
            if (graph[v][i] != INF && dist[i] > graph[v][i])
            {
                dist[i] = graph[v][i];
                path[i] = v;
            }
        }
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Initial(n);
    while (m--)
    {
        int a, b;
        T c;
        scanf("%d%d%lld", &a, &b, &c);
        if (graph[a][b] == INF || graph[a][b] > c) //重边
            graph[a][b] = graph[b][a] = c;
    }
    Prim(n);
    int order;
    scanf("%d", &order);
    while (order--)
    {
        int num = 0; //a到b的边数
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%lld\n", maxEdge[a][b]);
    }
    return 0;
}