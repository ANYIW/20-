#include <stdio.h>
#include <stdlib.h>
#define INF 65536
#define MAX 2001
typedef long long T;

T graph[MAX][MAX];
T dist[MAX];
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
        dist[v] = 0;
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
//堆排序
T edge[30000];
void Swap(int i, int j)
{
    int tmp = edge[i];
    edge[i] = edge[j];
    edge[j] = tmp;
}
void Restore(int i, int n)
{
    int tmp = edge[i];
    int parent, child;
    for (parent = i; (2 * parent + 1) <= n - 1; parent = child)
    {
        child = 2 * parent + 1;
        if (child != n - 1 && edge[child] < edge[child + 1])
            child++;
        if (tmp < edge[child])
            edge[parent] = edge[child];
        else
            break;
    }
    edge[parent] = tmp;
}
void Build(int n)
{
    for (int i = (n - 2) / 2; i >= 0; i--)
        Restore(i, n);
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
        int last = path[b];
        while (last != 1 && last != a)
        {
            edge[num++] = graph[last][b];
            b = last;
            last = path[b];
        }
        edge[num++] = graph[last][b];

        if (last != a)
        {
            last = path[a];
            while (last != 1)
            {
                edge[num++] = graph[last][a];
                a = last;
                last = path[a];
            }
            edge[num++] = graph[1][a];
        }
        Build(num);
        printf("%lld\n", edge[0]);
    }
    return 0;
}