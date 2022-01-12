#include <stdio.h>
#include <stdlib.h>
int visited[1000000];
int a[1000000]; //全局数组能比局部大开得大
void Reset(int m)
{
    for (int i = 0; i < m; i++)
        visited[i] = 0;
}
int main()
{
    int n, m; //组数、数组长度
    int result = 0;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%d", &a[i]);
        //从后往前扫描数组
        for (int i = m - 1; i >= 0; i--)
        {
            //直接乘出当前元素的倍数
            for (int j = 2; j * a[i] <= m; j++)
            {
                if (visited[j * a[i]] == 0)
                    result++;
            }
            visited[a[i]] = 1;
        }
        printf("%d\n", result);
        Reset(m);   //重置visited数组
        result = 0; //重置result
    }
    return 0;
}
/*
2
5
1 4 3 2 5
1//输出
5
5 4 3 2 1
5//输出
*/