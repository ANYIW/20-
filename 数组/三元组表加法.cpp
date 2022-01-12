#include <stdio.h>
#include <stdlib.h>
int a[5000][3];
int b[5000][3];
int c[5000][3];
int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &b[i][0], &b[i][1], &b[i][2]);
    }
    int aa = 0;
    int bb = 0;
    int cc = 0;
    while (aa < m && bb < n)
    {
        if (a[aa][0] < b[bb][0])//第0列为第一关键字
        {
            c[cc][0] = a[aa][0];
            c[cc][1] = a[aa][1];
            c[cc][2] = a[aa][2];
            cc++;
            aa++;
        }
        else
        {
            if (a[aa][0] == b[bb][0])
            {
                if (a[aa][1] < b[bb][1])//第1列为第二关键字
                {
                    c[cc][0] = a[aa][0];
                    c[cc][1] = a[aa][1];
                    c[cc][2] = a[aa][2];
                    cc++;
                    aa++;
                }
                else
                {
                    if (a[aa][1] == b[bb][1])
                    {
                        if (a[aa][2] + b[bb][2])
                        {
                            c[cc][0] = a[aa][0];
                            c[cc][1] = a[aa][1];
                            c[cc][2] = a[aa][2] + b[bb][2];
                            cc++;//系数不相抵消cc才自增
                        }
                        //cc++;
                        aa++;
                        bb++;
                    }
                    else
                    { //a[aa][1]>b[bb][1]
                        c[cc][0] = b[bb][0];
                        c[cc][1] = b[bb][1];
                        c[cc][2] = b[bb][2];
                        cc++;
                        bb++;
                    }
                }
            }
            else
            { //a[aa][0] > b[bb][0]
                c[cc][0] = b[bb][0];
                c[cc][1] = b[bb][1];
                c[cc][2] = b[bb][2];
                cc++;
                bb++;
            }
        }
    }
    //结尾处理
    while (aa < m)
    {
        c[cc][0] = a[aa][0];
        c[cc][1] = a[aa][1];
        c[cc][2] = a[aa][2];
        cc++;
        aa++;
    }
    while (bb < n)
    {
        c[cc][0] = b[bb][0];
        c[cc][1] = b[bb][1];
        c[cc][2] = b[bb][2];
        cc++;
        bb++;
    }
    for (int i = 0; i < cc; i++)
    {
        printf("%d %d %d\n", c[i][0], c[i][1], c[i][2]);
    }
    return 0;
}