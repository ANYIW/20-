#include <stdio.h>
#define INF 10e10
int collected[101];
long long cost[101][101];  //记录边的权重
long long dist[101][101];  //i到j最短路径的值
long long count[101][101]; //i到j最短路径的条数
void Reset(int n)
{
    for (int i = 1; i <= n; i++)
        collected[i] = 0;
}
void Initial(int n)
{
    for (int i = 1; i <= n; i++)
    {
        collected[i] = 0;
        for (int j = 1; j <= n; j++)
        {
            count[i][j] = 1; //图连通
            if (i != j)
            {
                //count[i][j] = 1;
                cost[i][j] = dist[i][j] = INF;
            }
        }
    }
}
//寻找v到其他各点的最短路径条数，填count[v][i]
void Dijkstra(int v, int n)
{
    while (1)
    {
        //找未被收录的点中dist最小者w
        int min = INF;
        int w = -1;
        for (int i = 1; i <= n; i++)
        {
            if (collected[i] == 0 && dist[v][i] < min)
            {
                min = dist[v][i];
                w = i;
            }
        }
        //全部点都被收录则退出循环
        if (w == -1)
            break;
        collected[w] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (collected[i] == 0 && cost[w][i] != INF)
            {
                if (dist[v][i] > dist[v][w] + cost[w][i])
                {
                    dist[v][i] = dist[v][w] + cost[w][i];
                    count[v][i] = count[v][w];
                }
                else if (dist[v][i] == dist[v][w] + cost[w][i])
                {
                    count[v][i] += count[v][w];
                }
            }
        }
    }
}
void Print(int n){
    for (int k = 1; k <= n; k++)
    {
        double sum = 0;
        long long path = 0; //i到j经过k的最短路径条数
        for (int i = 1; i <= n; i++)
            if (i != k)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (j != k && j != i)
                    {
                        //以dist相等来确保k在i到j的最短路径上
                        if (dist[i][k] + dist[k][j] == dist[i][j])
                            path = count[i][k] * count[k][j];
                        else
                            path = 0;
                        sum += dist[i][j] * (double)path / count[i][j]; //i!=j，count[i][j]!=0
                    }
                }
            }
        printf("%.3lf\n", sum);
    }
}
int main()
{
    int n, e;
    scanf("%d%d", &n, &e);
    Initial(n);
    while (e--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        cost[a][b] = c;
        cost[b][a] = c;
    }
    for (int i = 1; i <= n; i++)
    {
        Dijkstra(i, n);
        Reset(n);
    }
    Print(n);
    return 0;
}
/*
4 4
3 2 6
4 3 1
1 3 9
4 1 1
0.000
0.000
30.000
20.000
*/