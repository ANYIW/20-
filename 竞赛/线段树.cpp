#include <stdio.h>
struct Node{
    long long sum;
    int left;
    int right;
};
//下标从1有效
int a[1000001];
struct Node tree[2000002];
//自底向上建立线段树的结点tree[i]
//l：tree[i]对应a数组的左边界
//r：tree[i]对应a数组的右边界
void Build(int i,int l,int r) {
    tree[i].left=l;
    tree[i].right=r;
    if(l==r){
        tree[i].sum=a[l];
        return;
    }
    int mid=(l+r)/2;
    Build(i*2,l,mid);
    Build(i*2+1,mid+1,r);
    tree[i].sum=tree[i*2].sum+tree[i*2+1].sum;
}
//考察线段树结点tree[i]
//l：a数组目标区间的左边界
//r：a数组目标区间的右边界
//返回目标区间累加和
long long Add(int i,int l,int r){
    //tree[i]与目标区间完全重合
    if(tree[i].left>=l&&tree[i].right<=r)
    return tree[i].sum;
    //tree[i]与目标区间不重叠
    if(tree[i].left>r||tree[i].right<l)
    return 0;
    //tree[i]与目标区间有重叠部分
    long long sum=0;
    //左子树有重叠
    if(tree[i*2].right>=l)
    sum+=Add(i*2,l,r);
    //右子树有重叠
    if(tree[i*2+1].left<=r)
    sum+=Add(i*2+1,l,r);
    return sum;
}
//考察tree[i]
//将a[j]加上k
void Change(int i,int j,int k){
    //找到a[j]对应的叶结点
    if(tree[i].left==tree[i].right){
        tree[i].sum+=k;
        return;
    }
    //往a[j]所在的子树递归
    if(j<=tree[i*2].right)
    Change(i*2,j,k);
    else if(j>=tree[i*2+1].left)
    Change(i*2+1,j,k);
    //更新每个包含a[j]的结点
    tree[i].sum=tree[i*2].sum+tree[i*2+1].sum;
}
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    Build(1,1,n);
    while(q--){
        int order;
        scanf("%d",&order);
        if(order==1){
            int j,k;
            scanf("%d%d",&j,&k);
            Change(1,j,k);
        }
        else if(order==2){
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",Add(1,l,r));
        }
    }
    return 0;
}