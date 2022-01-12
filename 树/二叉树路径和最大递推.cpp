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
int max = -1000000;
int result[200]; //下标从0开始
int num = 200;   //结果元素个数
int curr[200];   //保存当前路径，下标从1开始
int singleMax=-1000000;//单结点最大值，确保 2 -2 3 -2 2 的情况正确

//当前考察的结点、当前子数组累加和、
//当前路径最大子数组起始下标前一个位置、当前路径最大子数组终止下标
void Find(Ptr node, int sum, int begin, int end)
{
    //递归出口
    if (node == NULL)
        return;
    //考察单结点是否等于最大值
    if(node->data==max){
        num=0;
        result[num++]=max;
    }
    //维护当前路径、sum、begin、end
    curr[++end] = node->data;
    sum += node->data;
    if (sum <= 0) 
    {//当前子数组和不可能使后续子数组和增大，注意取等！！！因为要取较短者
        begin = end; //重新起头
        sum = 0;
    }else if(sum>max)
    { //不取等，取靠左上方的路径
        max=sum;
        num=0;
        for(int i=begin+1;i<=end;i++)
        result[num++]=curr[i];
    }
    else if (sum == max)
    {
        //取较短路径
        if(end-begin<num){
            num=0;
            for(int i=begin+1;i<=end;i++)
            result[num++]=curr[i];
        }
    }
    
    //继续考察
    Find(node->left, sum, begin, end);
    Find(node->right, sum, begin, end);
}
int main()
{
    Ptr root = Create();
    Find(root, 0, 0, 0);
    printf("%d\n", max);
    if(max==singleMax)//注意！！！
    printf("%d ",singleMax);
    else{
        for (int i = 0; i < num; i++)
            printf("%d ", result[i]);
    }  
    return 0;
}
/*
1 2 0 0 3 0 0
4
1 3

-1 2 0 0 3 4 0 0 0
7
3 4

3 2 0 0 -1 4 0 0 0
6
3 -1 4

2 -2 3 -2 2 0 0 0 0 0 0
3
3
*/