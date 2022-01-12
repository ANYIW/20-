#include <stdio.h>
#include <stdlib.h>
#define INF 10e8
typedef struct Edge *PtrE;
struct Edge
{
    int weight;
    int adj;
    PtrE next;
};
typedef struct Vertex *PtrV;
struct Vertex
{
    //int data;
    PtrE first;
};
PtrV head[20001];
int dist1[20001];
int dist2[20001];
int collected[20001];//是否在队列中
int transfer = 0; //假设不换乘
int queue[20001]; //SPFA
int front = -1;
int rear = -1;
void Initial(int n)
{
    transfer = 0;
    front=rear=-1;
    for (int i = 1; i <= n; i++)
    {
        if (head[i] == NULL)
            head[i] = (PtrV)malloc(sizeof(struct Vertex));
        head[i]->first = NULL;
        dist1[i] = dist2[i]=INF;
        collected[i] = 0;
    }
}
void Reset(int n)
{
    front=rear=-1;
    for (int i = 1; i <= n; i++)
    {
        collected[i] = 0;
    }
}
//最坏O(ne)
void SPFA(int* dist,int v, int n)
{
    dist[v] = 0;
    queue[++rear]=v;
    collected[v] = 1;
    PtrE e = head[v]->first;
    /*while (e)
    {
        dist[e->adj] = e->weight;
        e = e->next;
    }*/
    //迭代n-1次，找出至多包含n-1条边的最短路径
    while(front!=rear){
        int out=queue[++front];
        collected[out]=0;
        PtrE e = head[out]->first;
        while (e)
        {
            if (dist[e->adj] > dist[out] + e->weight)
            {
                dist[e->adj] = dist[out] + e->weight;
                //只有dist被更新的点在下一轮迭代dist才可能再被更新
                if(collected[e->adj]==0){
                    queue[++rear]=e->adj;
                    collected[e->adj]=1;
                }
            }
            e = e->next;
        }
    }
}
void Release(int n)
{
    PtrE e1, e2;
    for (int i = 1; i <= n; i++)
    {
        e1 = head[i]->first;
        while (e1)
        {
            e2 = e1->next;
            free(e1);
            e1 = e2;
        }
    }
}
int main()
{
    int n, s, t; //顶点总数、起点、终点
    while (scanf("%d%d%d", &n, &s, &t) != EOF)
    {
        Initial(n);
        int path;
        scanf("%d", &path); //公交车路径条数
        while (path--)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            PtrE e1 = (PtrE)malloc(sizeof(struct Edge));
            e1->adj = b;
            e1->weight = c;
            e1->next = head[a]->first;
            head[a]->first = e1; //从头插入
            //无向图
            PtrE e2 = (PtrE)malloc(sizeof(struct Edge));
            e2->adj = a;
            e2->weight = c;
            e2->next = head[b]->first;
            head[b]->first = e2; //从头插入
        }
        SPFA(dist1,s, n);
        int min = dist1[t]; //只坐公交的最短路径长
        Reset(n);
        SPFA(dist2,t,n);//以终点为起点的最短路径

        scanf("%d", &path); //轻轨路径条数
        //考察每一条边
        while (path--)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            
            if (dist1[a]+c+dist2[b] < min)
            {
                min = dist1[a] + c + dist2[b];
                transfer = a;
            }else if(dist1[b]+c+dist2[a]<min){
                min = dist1[b] + c + dist2[a];
                transfer=b;
            }
        }
        //输出
        printf("%d\n", min);
        if (transfer)
            printf("%d\n", transfer);
        else
            printf("no metro\n");
        Release(n);
    }
    return 0;
}