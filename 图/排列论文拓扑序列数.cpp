#include <stdio.h>
#include <stdlib.h>
typedef struct Edge* PtrE;
struct Edge{
    int adj;
    PtrE next;
};
typedef struct Vertex* PtrV;
struct Vertex{
    PtrE first;
};
PtrV head[101];
int degree[101];
void Initial(int n){
    for(int i=1;i<=n;i++){
        degree[i]=0;
        if(head[i]==NULL)
        head[i]=(PtrV)malloc(sizeof(struct Vertex));
        head[i]->first=NULL;
    }
}
int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        Initial(n);
        int result=1;//假设拓扑序列唯一
        while(m--){
            int a,b;
            scanf("%d%d",&a,&b);
            degree[b]++;
            PtrE e=(PtrE)malloc(sizeof(struct Edge));
            e->adj=b;
            e->next=head[a]->first;
            head[a]->first=e;//从头插入
        }
        //拓扑
        int stack[100];
        int top=-1;
        int count=0;//同一时刻度为0的点的个数
        for(int i=1;i<=n;i++){
            if(degree[i]==0){
                stack[++top]=i;
                count++;
            }
        }
        if(count>1)
        result=2;
        while(top!=-1){
            int v=stack[top--];
            PtrE e=head[v]->first;
            count=0;
            while(e){
                degree[e->adj]--;
                if(degree[e->adj]==0){
                    stack[++top]=e->adj;
                    count++;
                }
                e=e->next;
            }
            if(count>1)
            result=2;
        }
        //输出
        for(int i=1;i<=n;i++){
            if(degree[i]!=0){
                result=0;
                break;
            }
        }
        printf("%d\n",result);
    }
    return 0;
}