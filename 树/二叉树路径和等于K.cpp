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
int result[150000]; //下标从0开始
int num = 150001;   //结果元素个数
int stack[150000];  //保存当前路径，下标从1开始
int top = 0;
int prefix[150000];
//当前考察的结点，目标路径长
void Find(Ptr node, int k)
{
    //递归出口
    if (node == NULL)
        return;
    //维护当前路径、前缀和
    stack[++top] = node->data;
    prefix[top] = prefix[top - 1] + node->data;
    //是否存在以stack[top]为终点、和为k的路径
    for (int i = 0; i <= top; i++)
    {
        //可取等，即为靠右下方的路径
        if (prefix[top] - prefix[i] == k && top - i <= num)
        {
            num = 0;
            for (int j = i + 1; j <= top; j++)
                result[num++] = stack[j];
        }
    }
    //继续寻找
    Find(node->left, k);
    Find(node->right, k);
    top--; //当前分支考察完
}
int main()
{
    int T, K;
    Ptr root;
    scanf("%d", &T);
    while (T--)
    {
        root = Create();
        scanf("%d", &K);

        top = 0;
        num = 150001;
        Find(root, K);
        //输出
        if (num == 150001)
            printf("no available path");
        else
        {
            for (int i = 0; i < num; i++)
                printf("%d ", result[i]);
        }
        //最后一行末尾不加换行符
        if (T >= 0)
            printf("\n");
    }
    return 0;
}
/*
2
8 5 1 0 0 2 0 0 7 0 0 7
7 //输出
8 5 1 0 0 2 0 0 7 0 0 6
5 1 //输出
*/