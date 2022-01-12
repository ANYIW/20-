#include <stdio.h>
#define INF 10e6
int D[100][100];
//初始时假设各点之间不连通
void Reset(int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                D[i][j] = INF;
}
void Floyd(int n)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (D[i][j] > D[i][k] + D[k][j])
                    D[i][j] = D[i][k] + D[k][j];
}
int main()
{
    int n, e;
    while (scanf("%d%d", &n, &e) != EOF)
    {
        Reset(n);
        while (e--)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            D[a][b] = c;
            D[b][a] = c; //无向图！！！！！！
        }
        Floyd(n);
        //考察每一点
        int min = INF;
        int city;
        for (int i = 0; i < n; i++)
        {
            int sum = 0;
            for (int j = 0; j < n; j++)
                sum += D[i][j];
            //不取等，多个城市满足要求取编号最小者
            if (sum < min)
            {
                min = sum;
                city = i;
            }
        }
        printf("%d\n", city);
    }
    return 0;
}
/*
6 5
0 1 1
0 2 1
0 3 1
0 4 1
0 5 1
0    
4 5  
0 1 1
0 2 5
1 2 2
1 3 4
2 3 1
1*/