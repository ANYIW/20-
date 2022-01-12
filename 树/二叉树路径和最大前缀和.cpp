#include <stdio.h>
#include <stdlib.h>
typedef struct Node *Ptr;
struct Node
{
    int data;
    Ptr left;
    Ptr right;
};
Ptr Create()
{
    int d;
    scanf("%d", &d);
    //递归出口
    if (d == 0)
        return NULL;
    //先序创建树结点
    Ptr node = (Ptr)malloc(sizeof(struct Node));
    node->data = d;
    node->left = Create();
    node->right = Create();
    return node;
}
int max=-1000000;
int result[200]; //下标从0开始
int num = 200;   //结果元素个数
int out[200];  //保存当前路径，下标从1开始
int top = 0;
int prefix[200];
//当前考察的结点
void Find(Ptr node)
{
    //递归出口
    if (node == NULL)
        return;
    //维护当前路径、前缀和
    out[++top] = node->data;
    prefix[top] = prefix[top - 1] + node->data;
    //更新以out[top]为终点、和最大的路径，以及max
    for (int i = 0; i <= top; i++)
    {
        //可能会有更短的
        if (prefix[top] - prefix[i] ==max )
        {
            //条件不取等，即为靠左上方的路径
            if(top-i<num){
                num = 0;
                for (int j = i + 1; j <= top; j++)
                    result[num++] = out[j];
            }
        }else if(prefix[top]-prefix[i]>max){
            max=prefix[top]-prefix[i];
            num = 0;
            for (int j = i + 1; j <= top; j++)
                result[num++] = out[j];
        }
    }
    //继续寻找
    Find(node->left);
    Find(node->right);
    top--; //当前分支考察完
}
int main(){
    Ptr root=Create();
    Find(root);
    printf("%d\n",max);
    for(int i=0;i<num;i++)
    printf("%d ",result[i]);
    return 0;
}
/*
1 2 0 0 3 0 0//输入
4
1 3
-1 2 0 0 3 4 0 0 0//输入
7
3 4
3 2 0 0 -1 4 0 0 0//输入
6
3 -1 4
*/