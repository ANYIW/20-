#include <stdio.h>
#define INF 10e6
int dist[200][200];
void Initial(int n){
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    if(i!=j)
    dist[i][j]=INF;
}
void Floyd(int n){
    for(int k=0;k<n;k++)
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    if(dist[i][j]>dist[i][k]+dist[k][j])
    dist[i][j]=dist[i][k]+dist[k][j];
}
int main(){
    int n,m;
    while((scanf("%d%d",&n,&m))!=EOF){
        Initial(n);
        //有向图
        for(int i=0;i<n;i++){
            int v;
            int out;
            scanf("%d%d",&v,&out);
            while(out--){
                int w;
                scanf("%d",&w);
                dist[v][w]=1;
            }
        }
        Floyd(n);
        //查询
        while(m--){
            int v,w;
            scanf("%d%d",&v,&w);
            if(dist[v][w]!=INF)
            printf("%d\n",dist[v][w]);
            else printf("connection impossible\n");
        }
    }
    return 0;
}