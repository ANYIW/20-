#include <stdio.h>
#include <stdlib.h>
#define INF 10e9
#define MAX 1500
typedef long long Type;
typedef struct Edge *PtrE;
struct Edge
{
    Type weight;
    int v1, v2;
};
PtrE heap[MAX]; //最小堆
int num = 0;    //堆中元素个数
int collected[MAX];
void Initial(int n, int e)
{
    num = 0;
    for (int i = 0; i < n; i++)
        collected[i] = 0;
    //哨兵
    heap[0] = (PtrE)malloc(sizeof(struct Edge));
    heap[0]->weight = -1;
    for (int i = 1; i <= e; i++)
        heap[i] = NULL;
}
void Insert(PtrE edge)
{
    if (edge == NULL)
        return;
    num++;
    int i;
    for (i = num; heap[i / 2]->weight > edge->weight; i /= 2)
        heap[i] = heap[i / 2];
    heap[i] = edge;
}
PtrE Delete()
{
    if (num == 0)
        return NULL;
    PtrE min = heap[1];
    PtrE tmp = heap[num--];
    int parent, child;
    for (parent = 1; 2 * parent <= num; parent = child)
    {
        child = 2 * parent;
        if (child + 1 <= num && heap[child]->weight > heap[child + 1]->weight)
            child++;
        if (tmp->weight > heap[child]->weight)
            heap[parent] = heap[child];
        else
            break;
    }
    heap[parent] = tmp;
    return min;
}
int main()
{
    int n, e;
    while (scanf("%d%d", &n, &e) != EOF)
    {
        Type sum = 0;
        int count = 0; //MST中边的条数
        //构建最小堆
        Initial(n, e);
        while (e--)
        {
            PtrE edge = (PtrE)malloc(sizeof(struct Edge));
            scanf("%d%d%lld", &edge->v1, &edge->v2, &edge->weight);
            Insert(edge);
        }
        //寻找不构成环的最小边
        PtrE edge = Delete();
        while (edge)
        {
            if (collected[edge->v1] == 0 || collected[edge->v2] == 0)
            {
                sum += edge->weight;
                count++;
                collected[edge->v1] = collected[edge->v2] = 1;
            }
            edge = Delete();
        }
        //输出
        if (count == n - 1)
            printf("%lld\n", sum);
        else
            printf("There is no minimum spanning tree.\n");
    }
    return 0;
}
/*
4 5
0 1 1
0 3 1
1 3 5
1 2 1
2 3 8
4 2
0 1 1
2 3 8
3
There is no minimum spanning tree.*/