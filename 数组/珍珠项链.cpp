#include <stdio.h>
int father[30001];//father[i]==0则i为集合代表元
int Find(int a){
    if(father[a]==0)
    return a;
    return father[a]=Find(father[a]);
}
//将a所在集合并入b所在集合
void Union(int a,int b){
    int aa=Find(a);
    int bb=Find(b);
    if(aa==bb)
    return;
    father[aa]=bb;
}
void Reset(int n){
    for(int i=1;i<=n;i++)
    father[i]=0;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            Union(a,b);
        }
        for(int i=1;i<=n;i++)
        printf("%d ",Find(i));
        printf("\n");
        Reset(n);
    }
    return 0;
}
/*
2
4 2
2 1
4 3
1 1 3 3 //输出
5 4
1 2
2 3
4 5
1 3
3 3 3 5 5 //输出
*/