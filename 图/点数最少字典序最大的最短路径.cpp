#include <stdio.h>
#include <stdlib.h>
#define INF 10e6
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
PtrV head[20000];     //下标代表顶点编号
int dist[20000];      //当前最短路径长度
int collected[20000]; //是否被收录
int path[20000];      //路径上该点前一个顶点
int count[20000];     //当前最短路径包含顶点个数

//返回未被收录点中dist最小者，不存在则返回-1
int ScanMin(int n)
{
    int min = INF;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (collected[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
//返回字典序较小的路径中最后一个顶点，v1、v2分别为两条路径最后一个顶点
int Compare(int v1, int v2)
{
    int stack1[20000];
    int top1 = -1, tmp1 = v1;
    int stack2[20000];
    int top2 = -1, tmp2 = v2;
    while (tmp1)
    {
        stack1[++top1] = tmp1;
        tmp1 = path[tmp1];
    }
    while (tmp2)
    {
        stack2[++top2] = tmp2;
        tmp2 = path[tmp2];
    }
    //按理来说top1==top2
    int pop1, pop2;
    while (top1 != -1 && top2 != -1)
    {
        pop1 = stack1[top1--];
        pop2 = stack2[top2--];
        if (pop1 > pop2)
            return v2;
        if (pop2 > pop1)
            return v1;
    }
}
int main()
{
    int n, e;
    scanf("%d%d", &n, &e);
    //初始化顶点和dist
    for (int i = 0; i < n; i++)
    {
        head[i] = (PtrV)malloc(sizeof(struct Vertex));
        head[i]->first = NULL;
        dist[i] = INF;
    }
    //生成边，从头插入
    while (e--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        PtrE edge = (PtrE)malloc(sizeof(struct Edge));
        edge->adj = b;
        edge->weight = c;
        edge->next = head[a]->first;
        head[a]->first = edge;
    }
    //初始状态
    //dist[0]=0;
    collected[0] = 1;
    //path[0]=0;
    //count[0]=0;
    PtrE tmp = head[0]->first;
    while (tmp)
    {
        dist[tmp->adj] = tmp->weight;
        //path[tmp->adj]=0;
        count[tmp->adj] = 1;
        tmp = tmp->next;
    }
    //Dijkstra
    while (1)
    {
        int v = ScanMin(n);
        if (v == -1)
            break;
        collected[v] = 1;
        //更新v的邻接点
        PtrE tmp = head[v]->first;
        while (tmp)
        {
            //选路径较短者
            if(collected[tmp->adj]==0){
                if (dist[tmp->adj] > dist[v] + tmp->weight)
                {
                    dist[tmp->adj] = dist[v] + tmp->weight;
                    path[tmp->adj] = v;
                    count[tmp->adj] = count[v] + 1;
                }
                else if (dist[tmp->adj] == dist[v] + tmp->weight)
                {
                    //路径等长，选顶点数较少者
                    if (count[v] + 1 < count[tmp->adj])
                    {
                        path[tmp->adj] = v;
                        count[tmp->adj] = count[v] + 1;
                    }
                    else if (count[v] + 1 == count[tmp->adj])
                    {
                        //顶点数相等，选字典序较小者
                        path[tmp->adj] = Compare(v, path[tmp->adj]);
                    }
                }
            } 
            tmp = tmp->next;
        }
    }
    //输出
    int stack[20000];
    int top = -1;
    for (int i = 1; i < n; i++)
    {
        if (dist[i] != INF)
        {
            int tmp = i;
            while (tmp)
            {
                stack[++top] = tmp;
                tmp = path[tmp];
            }
            printf("0");
            while (top != -1)
                printf("->%d", stack[top--]);
            printf("\n");
        }
    }
    return 0;
}
/*
6 7
0 1 1
1 4 2
4 5 3
0 3 4
3 5 2
0 2 5
2 5 1
0->1
0->2
0->3
0->1->4
0->2->5

5 7
3 4 1
2 4 5
2 3 4
1 3 2
2 1 1
0 1 4
0 2 2
0->2->1
0->2
0->2->1->3
0->2->1->3->4

5 6
3 4 1
2 4 5
2 3 4
1 3 2
0 1 4
0 2 2
0->1
0->2
0->1->3
0->2->4*/