#include <stdio.h>
#define INF 10E10
long long dist[101][101];
long long count[101][101];
void Initial(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            count[i][j]=1;//图连通
            if(i!=j)
            dist[i][j] = INF;
        }
    }
}
//Floyd也可以求最短路径条数
void Floyd(int n)
{
    for (int t = 1; t <= n; t++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dist[i][j] > dist[i][t] + dist[t][j] && i != j && i != t && j != t)
                {
                    dist[i][j] = dist[i][t] + dist[t][j];
                    count[i][j] = count[i][t] * count[t][j];
                }
                else if (dist[i][j] == dist[i][t] + dist[t][j] && i != j && i != t && j != t)
                {
                    count[i][j] += count[i][t] * count[t][j]; //发现一条从i到j等长的路
                }
            }
        }
    }
}
void Print(int n)
{
    for (int k = 1; k <= n; k++)
    {
        double sum = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                //以dist相等来确保k在i到j的最短路径上
                if (dist[i][j] == dist[i][k] + dist[k][j] && i != j && i != k && j != k)
                {
                    sum += dist[i][j] * (double)count[i][k] * count[k][j] / count[i][j];
                }
            }
        }
        printf("%.3lf\n", sum);
    }
}
int main()
{
    int n,e;
    scanf("%d %d", &n, &e);
    Initial(n);
    while (e--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        dist[a][b] = c;
        dist[b][a] = c;
    }
    Floyd(n);
    Print(n);
}
/*
4 4
3 2 6
4 3 1
1 3 9
4 1 1
*/