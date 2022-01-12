#include <stdio.h>
int a[2000001];
long long prefix[2000001];//前缀和
long long diff[2000001];//prefix的差分值
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        prefix[i]=prefix[i-1]+a[i];
        diff[i]=prefix[i]-prefix[i-1];
    }
    while(q--){
        int order;
        scanf("%d",&order);
        int flag=0;//标记是否执行过1操作
        if(order==1){
            int i;
            long long x;
            scanf("%d%lld",&i,&x);
            diff[i]+=x;
            flag=1;
        }
        else if(order==2){
            int l,r;
            scanf("%d%d",&l,&r);
            //由diff恢复prefix
            if(flag){
                for (int i = 1; i <= n; i++)
                    prefix[i] = prefix[i - 1] + diff[i];
            }
            //输出
            printf("%lld\n",prefix[r]-prefix[l-1]);
        }
    }
    return 0;
}
/*
3 2
1 2 3
1 2 0
2 1 3
6*/