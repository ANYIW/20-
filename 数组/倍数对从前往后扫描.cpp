#include <stdio.h>
#include <stdlib.h>
#include <math.h>//sqrt
int visited[1000000];
void Reset(int m)
{
    for (int i = 0; i < m; i++)
        visited[i] = 0;
}
int main()
{
    int n, m, k; //组数、数组长度、暂存数组元素
    int result = 0;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &k);
            if (k == 1)//
            {
                visited[1] = 1;
                continue;
            }
            //2*3=6的情况用sqrt限制
            for (int j = 1; (j <= sqrt(k)) /*&& ((k % j) == 0)*/; j++)
            {
                if (k % j == 0)
                {
                    if (visited[j] == 0) //没被访问过则必定在k后出现
                        result++;
                    //1*3=3 2*2=4
                    if (k / j != k && k / j != j && visited[k / j] == 0)
                        result++;
                }
            }
            visited[k] = 1; //k被访问过了
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