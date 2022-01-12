//求每条从根结点到叶结点的路径的失败函数，找到最大f[n-1]
#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node{
    int data;
    Ptr left;
    Ptr right;
};
//构建二叉树
Ptr Create(){
    int d;
    scanf("%d",&d);
    //递归出口
    if(d==0)
    return NULL;
    //创建树结点
    Ptr node=(Ptr)malloc(sizeof(struct Node));
    node->data=d;
    node->left=Create();
    node->right=Create();
    return node;
}
//计算最长前后缀路径
int length=-1;
int stack[150000];
int top=-1;
//求栈内元素的失败函数，即为路径长度（结点数-1）
int f[150000];
void Fail(int top){
    int k=-1;
    f[0]=-1;
    for(int i=1;i<=top;i++){//元素个数为top+1
        while(k>=0&&stack[k+1]!=stack[i])
        k=f[k];
        if(stack[k+1]==stack[i])
        k++;
        f[i]=k;
    }
}
//回溯法
void Push(Ptr node){
    //合法检测
    if(node==NULL)
    return;
    //叶结点，开始计算栈内元素的失败函数，更新最长路径
    if(node->left==NULL&&node->right==NULL){
        stack[++top]=node->data;
        Fail(top);
        if(f[top]>length)
        length=f[top];
        top--;//弹出叶结点node
        return;
    }
    //压栈
    stack[++top]=node->data;
    //先序压栈
    Push(node->left);
    Push(node->right);
    top--;//弹出node
}
//释放
void Release(Ptr root){
    if(root==NULL)
    return;
    Release(root->left);
    Release(root->right);
    free(root);
}
int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        Ptr root=Create();
        //重置
        top=-1;
        length=-1;
        Push(root);
        Release(root);
        printf("%d\n",length);
    }
    return 0;
}
/*
4
1 2 3 1 2 3 1 0 0 0 0 0 0 0 0
1 2 3 4 0 0 0 1 2 0 0 0 0
1 2 0 0 3 0 4 0 0
1 1 0 0 1 0 0
输出
3
1
-1
0*/