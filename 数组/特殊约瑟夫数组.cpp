#include <stdio.h>
/*下标[1,n]内循环
if ((curr - 1) % n)
                curr = (curr - 1) % n;
            else
                curr = n;
if (curr + 1 == n)
                curr = n;
            else
                curr = (curr + 1) % n;
下标[0,n-1]内循环
if(curr-1<0)
curr=n-1;
curr=(curr+1)%n;
*/
int a[1001]; //0为未出队，1为出队，下标为编号
int main()
{
    int n, m, k; //n为capacity
    int out = 0; //当前出队人数
    scanf("%d%d%d", &n, &m, &k);
    int curr = 1; //起始报数的人
    while (1)
    {
        //逆时针报数m次
        int i = 0;
        while (1)
        {
            if (a[curr] == 0) //未出队才算数
            {
                i++; //报数
                if (i == m)
                    break;
            }
            if ((curr - 1) % n)
                curr = (curr - 1) % n;
            else
                curr = n;
        }
        a[curr] = 1; //curr出队
        printf("%d ", curr);
        out++;
        if (out == n)
            break;
        //逆时针寻找下一个未出队的人开始报数
        while (a[curr])
        {
            if ((curr - 1) % n)
                curr = (curr - 1) % n; 
            else
                curr = n;
        }

        //顺时针报数k次
        int j = 0;
        while (1)
        {
            if (a[curr] == 0) //未出队才算数
            {
                j++;
                if (j == k)
                    break;
            }
            if (curr + 1 == n)
                curr = n;
            else
                curr = (curr + 1) % n;
        }
        a[curr] = 1;
        printf("%d ", curr);
        out++;
        if (out == n)
            break;
        //顺时针寻找下一个未出队的人开始报数
        while (a[curr])
        {
            if (curr + 1 == n)
                curr = n;
            else
                curr = (curr + 1) % n;
        }
    }
    return 0;
}