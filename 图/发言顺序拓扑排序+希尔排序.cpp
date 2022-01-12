#include <stdio.h>
#include <stdlib.h>
typedef struct Edge *PtrE;
struct Edge
{
    int adj;
    PtrE next;
};
typedef struct Vertex *PtrV;
struct Vertex
{
    PtrE first;
};
PtrV head[300];
int degree[300];
int queue[600];
int front = -1;
int rear = -1;
int result[300];
int num = 0;
void Initial(int n)
{
    for (int i = 0; i < n; i++)
    {
        head[i] = (PtrV)malloc(sizeof(struct Vertex));
        head[i]->first = NULL;
    }
}
//对queue下标从begin到end的部分进行排序
int gap[] = {1, 4, 10, 23, 57, 132, 301};
void Shell(int *queue, int begin, int end)
{
    int d, i;
    for (i = 0; end - begin + 1 > gap[i]; i++)
        ; //待排元素个数为end-begin+1，分号别漏！
    for (i -= 1; i >= 0; i--)
    {
        d = gap[i];
        for (int j = begin + d; j <= end; j++)
        {
            int tmp = queue[j];
            int k;
            for (k = j; k >= begin + d && queue[k - d] > tmp; k -= d)
                queue[k] = queue[k - d];
            queue[k] = tmp;
        }
    }
}
int main()
{
    int n, e;
    scanf("%d%d", &n, &e);
    Initial(n);
    //读图
    while (e--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        degree[b]++;
        PtrE edge = (PtrE)malloc(sizeof(struct Edge));
        edge->adj = b;
        edge->next = head[a]->first;
        head[a]->first = edge;
    }
    //度为0的点入队
    for (int i = 0; i < n; i++)
    {
        if (degree[i] == 0)
            queue[++rear] = i;
    }
    //Shell();首次入队序列一定递增

    //拓扑排序
    int oldBegin = front + 1;
    int oldEnd = rear;
    while (front != rear)
    {
        while (front != oldEnd)
        {
            int out = queue[++front];
            PtrE edge = head[out]->first;
            while (edge)
            {
                degree[edge->adj]--;
                if (degree[edge->adj] == 0)
                    queue[++rear] = edge->adj;
                edge = edge->next;
            }
        }
        //保存结果
        for (int i = oldBegin; i <= oldEnd; i++)
            result[num++] = queue[i];
        oldBegin = oldEnd + 1;
        oldEnd = rear;
        //排序
        Shell(queue, oldBegin, oldEnd);
    }
    //输出
    for (int i = 0; i < num; i++)
        printf("%d ", result[i]);
    return 0;
}
/*
8 7
4 0
2 5
3 7
2 4
3 6
1 2
1 3
1 2 3 4 5 6 7 0

12 10
4 0
2 5
3 7
2 4
3 6
1 2
1 3
8 9
8 11
11 10
1 8 2 3 9 11 4 5 6 7 10 0*/