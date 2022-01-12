#include <stdio.h>
int prefix[100050]; //prefix[0]作为哨兵
int queue[100050];  //空：front==rear
int main()
{
    int n, m;
    int curr;
    int front = 0;
    int rear = 0;
    int minTime;
    while (scanf("%d%d", &n, &m) == 2)
    {
        //重置
        front = 0;
        rear = 0;
        minTime = n + 1;
        //构造前缀和数组
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &curr);
            prefix[i] = prefix[i - 1] + curr; //prefix[0]==0
        }

        //构造单调递增队列
        for (int i = 1; i <= n; i++)
        {
            while ((front != rear) && prefix[i] <= prefix[queue[rear]])
                rear--;
            queue[++rear] = i; //存下标

            //缩短数组长度
            while ((front != rear) && prefix[queue[rear]] - prefix[queue[front + 1]] > m)
                front++;

            //队尾对应的下标和队头前一个元素对应的下标，即front，确定了当前一轮最短且和大于m的子数组
            //更新之前的最短子数组
            if (prefix[queue[rear]] - prefix[queue[front]] > m && queue[rear] - queue[front] < minTime)
                minTime = queue[rear] - queue[front];

            //队列只有1个元素的情况
            if (front + 1 == rear && prefix[queue[rear]] > m)
            {
                minTime = 1;
                goto FLAG;
            }
        }
    FLAG:
        //输出
        if (minTime <= n)
            printf("%d\n", minTime);
        else
            printf("%d\n", -1);
    }
    return 0;
}
/*
7 20
3 5 1 9 -1 13 2
3//输出
10 19977
-164 -1961 -1083 4343 5434 715 5954 3339 5985 1984
5//输出
*/