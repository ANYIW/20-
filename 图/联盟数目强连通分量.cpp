#include <stdio.h>
int reach[101][101];
int father[101];
int Find(int v){
    if(father[v]<0)
    return v;
    return father[v]=Find(father[v]);//路径压缩
}
//b所在集合并入a所在集合
void Union(int a,int b){
    int fa=Find(a);
    int fb=Find(b);
    if(fa==fb)
    return;
    father[fa]+=father[fb];
    father[fb]=fa;
    return;
}
void Initial(int n){
    for(int i=1;i<=n;i++){
        father[i]=-1;//自成一个集合
        for(int j=1;j<=n;j++){
            if(i!=j)
            reach[i][j]=0;
            else reach[i][j]=1;
        }
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        Initial(n);
        for(int i=1;i<=n;i++)
        {
            int j;
            scanf("%d",&j);
            while(j){
                reach[i][j]=1;
                scanf("%d",&j);
            }
        }
        //Warshall
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(reach[i][j]||reach[i][k]&&reach[k][j])
                    reach[i][j]=1;
                }
            }
        }
        //生成强连通分量
        int num=n;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i!=j&&reach[i][j]&&reach[j][i]){
                    if(Find(i)!=Find(j)){
                        Union(i, j);
                        num--;
                    }  
                }
            }
        }
        printf("%d\n",num);
    }
    return 0;
}
/*
3
5 
2 4 3 0
4 5 0
0
0
1 0
3//输出
3
2 0
0
2 1 0
3//输出
3
2 0
3 0
0
3//输出
*/