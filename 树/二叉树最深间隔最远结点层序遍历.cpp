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
    //出口
    if (d == 0)
        return NULL;
    //创建
    Ptr node = (Ptr)malloc(sizeof(struct Node));
    node->data = d;
    node->left = Create();
    node->right = Create();
    return node;
}
int Depth(Ptr node, int level)
{
    if (node == NULL)
        return level;
    int left = Depth(node->left, level + 1);
    int right = Depth(node->right, level + 1);
    return (left > right) ? left : right;
}
Ptr queue[201];
int front = 0;
int rear = 0;
int first, last; //最深层首尾结点值
void LevelOrder(Ptr root, int depth)
{
    if (root == NULL)
        return;
    int currLevel = 0;
    queue[++rear] = root;
    queue[++rear] = NULL; //标志第一层结束
    while (front != rear)
    {
        Ptr out = queue[++front];
        if (out)
        {
            if (out->left)
                queue[++rear] = out->left;
            if (out->right)
                queue[++rear] = out->right;
        }
        else
        { //标志当前层结束
            currLevel++;
            queue[++rear] = NULL;
            if (currLevel == depth)
            {
                first = queue[front + 1]->data;
                last = queue[rear - 1]->data;
                return;
            }
        }
    }
}
int main()
{
    Ptr root = Create();
    int depth = Depth(root, -1);
    LevelOrder(root, depth);
    if (last - first >= 0)
        printf("%d", last - first);
    else
        printf("%d", (-1) * (last - first)); //输出绝对值
    return 0;
}