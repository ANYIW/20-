#include <stdio.h>
#include <stdlib.h>
typedef struct Edge *PtrE;
struct Edge
{
    int adj;
    int weight;
    PtrE next;
};
typedef struct Vertex *PtrV;
struct Vertex
{
    //int data;数组下标代表点的编号
    PtrE first;
};
PtrV vertex[20010];
int main()
{
    int n, e;
    scanf("%d%d", &n, &e);
    //初始化点
    for (int i = 0; i < n; i++)
    {
        vertex[i] = (PtrV)malloc(sizeof(struct Vertex));
        vertex[i]->first = NULL;
    }
    //构建邻接表
    while (e--)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        PtrE e = (PtrE)malloc(sizeof(struct Edge));
        e->adj = b;
        e->weight = w;
        e->next = NULL;
        PtrE front = NULL;
        PtrE rear = vertex[a]->first;
        while (rear && rear->adj < b)
        {
            front = rear;
            rear = rear->next;
        }
        //插在头
        if (front == NULL)
        {
            vertex[a]->first = e;
            e->next = rear;
        }
        else
        {
            front->next = e;
            e->next = rear;
        }
    }
    //删边
    int k;
    scanf("%d", &k);
    while (k--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        PtrE front = NULL;
        PtrE rear = vertex[a]->first;
        while (rear->adj != b)
        {
            front = rear;
            rear = rear->next;
        }
        //删除第一条边的情况
        if (front == NULL)
        {
            vertex[a]->first = rear->next;
            free(rear);
        }
        else
        {
            front->next = rear->next;
            free(rear);
        }
    }
    //输出
    for (int i = 0; i < n; i++)
    {
        PtrE e = vertex[i]->first;
        if (e)
        {
            printf("%d:", i);
            while (e)
            {
                printf("(%d,%d,%d)", i, e->adj, e->weight);
                e = e->next;
            }
            printf("\n");
        }
    }
    return 0;
}