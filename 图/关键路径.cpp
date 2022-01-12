#include <stdio.h>
#include <stdlib.h>
#define MAX 10e6 
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
    PtrE first;
};
PtrV head[201];
int degree[201];
int ve[201];
int vl[201];
void Initial(int n)
{
    for (int i = 1; i <= n; i++)
    {
        degree[i] = 0;
        ve[i]=0;
        vl[i]=MAX;
        if (head[i] == NULL)
            head[i] = (PtrV)malloc(sizeof(struct Vertex));
        head[i]->first = NULL;
    }
}
int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        Initial(n);
        while (m--)
        {
            int a, b,c;
            scanf("%d%d%d", &a, &b,&c);
            degree[b]++;
            PtrE e = (PtrE)malloc(sizeof(struct Edge));
            e->adj = b;
            e->weight=c;
            e->next=NULL;
            //按adj递增顺序插入
            PtrE p=NULL;
            PtrE q=head[a]->first;
            while(q&&q->adj<b){
                p=q;
                q=q->next;
            }
            if(p==NULL)
            { //插在头
                e->next=head[a]->first;
                head[a]->first=e;
            }
            else
            {
                p->next=e;
                e->next=q;
            }
        }
        //拓扑
        int stack[200];
        int top = -1;
        int count = 0; //度为0的点的个数
        for (int i = 1; i <= n; i++)
        {
            if (degree[i] == 0)
            {
                stack[++top] = i;
                count++;
            }
        }

        int stack1[200];//逆拓扑序列
        int top1=-1;
        while (top != -1)
        {
            int v = stack[top--];
            stack1[++top1]=v;
            PtrE e = head[v]->first;
            while (e)
            {
                //求ve
                if(ve[e->adj]<ve[v]+e->weight)
                ve[e->adj]=ve[v]+e->weight;

                degree[e->adj]--;
                if (degree[e->adj] == 0)
                {
                    stack[++top] = e->adj;
                    count++;
                }
                e = e->next;
            }
        }
        if(count!=n){
            printf("unworkable project\n");
            continue;
        }
        //求vl
        int sum = ve[stack1[top1]];
        vl[stack1[top1]]=sum;//汇点
        top1--;
        while(top1!=-1){
            int v=stack1[top1--];
            PtrE e=head[v]->first;
            while(e){
                if(vl[e->adj]-e->weight<vl[v])
                vl[v]=vl[e->adj]-e->weight;
                e=e->next;
            }
        }
        //输出
        printf("%d\n",sum);
        PtrE e=NULL;
        for(int i=1;i<=n;i++){
            e=head[i]->first;
            while(e){
                if(vl[e->adj]-e->weight==ve[i]){
                    printf("%d->%d\n",i,e->adj);
                }
                e=e->next;
            }
        }
    }
    return 0;
}