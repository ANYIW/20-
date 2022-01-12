#include <stdio.h>
#define INF 10e9
long long graph[1500][1500];
long long dist[1500];
int parent[1500];
long long sum = 0;

void Initial(int n){
    sum=0;
    for(int i=0;i<n;i++){
        dist[i] = INF;
        for(int j=0;j<n;j++)
        if(i!=j)
        graph[i][j]=INF;
    }
}
int ScanMin(int n){
    int index=-1;
    long long min=INF;
    for(int i=0;i<n;i++){
        if(dist[i]!=0&&dist[i]<min){
            index=i;
            min=dist[i];
        }
    }
    return index;
}
int Prim(int n){
    int count=0;//收入MST的点数
    dist[0]=0;
    count++;
    for(int i=0;i<n;i++){
        if(graph[0][i]!=INF){
            dist[i]=graph[0][i];
            parent[i]=0;
        }
    }
    while(1){
        int v=ScanMin(n);
        if(v==-1)
        break;
        sum += dist[v];
        dist[v]=0;
        count++;
        for(int i=0;i<n;i++){
            if(graph[v][i]!=INF&&dist[i]>graph[v][i]){
                dist[i]=graph[v][i];
                parent[i]=v;
            }
        }
    }
    if(count==n)
    return 1;
    else return 0;
}
int main(){
    int n,e;
    while (scanf("%d%d", &n, &e)!=EOF)
    {
        Initial(n);
        while (e--)
        {
            int a, b;
            long long c;
            scanf("%d%d%lld", &a, &b, &c);
            //考虑重边
            if(graph[a][b]==INF||graph[a][b]>c){
                graph[a][b] = c;
                graph[b][a] = c;
            } 
        }
        if (Prim(n))
            printf("%lld\n",sum);
        else printf("There is no minimum spanning tree.\n");
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