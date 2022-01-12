#include <stdio.h>
using namespace std;
struct node
{
    int data;
    node *firstChild;
    node *nextBrother;
};
node *CreateTree()
{
    int k;
    scanf("%d", &k);
    if (k == 0)
        return NULL;
    node *t = new node;
    t->data = k;
    t->firstChild = CreateTree();
    t->nextBrother = CreateTree();
    return t;
}
void Del(node *root)
{
    if (root == NULL)
        return;
    node *p = root->firstChild;
    node *next;
    while (p != NULL)
    {
        next = p->nextBrother;
        Del(p);
        p = next;
    }
    delete root;
}

int LeastCommonAncestors(node *root, int a, int b)
{
    int father[1000]; //存每个结点最近的祖先结点，类似图的path数组
    //非递归先序遍历
    node *stack[1000];
    int top = -1;
    //每次入栈后填栈顶结点的father
    stack[++top] = root;
    father[stack[top]->data] = 0;
    node *tmp = root->firstChild;
    int pre = root->data;//当前待入栈结点的father
    while (1)
    {
        while (tmp)
        {
            stack[++top] = tmp;
            father[stack[top]->data] = pre;
            pre = stack[top]->data;
            tmp = tmp->firstChild;
        }

        if (top == -1)
            break;
        tmp = stack[top--];   
        pre = stack[top]->data;//更新pre
        tmp = tmp->nextBrother;
    }
    //寻找最近公共祖先
    int array[1000]; //由近及远，存a的祖先
    int num = 0;
    while (father[a] != 0)
    {
        array[num++] = father[a];
        a = father[a];
    }
    //逐一比较b由近及远的每一个祖先和a由近及远的每一个祖先
    while (father[b] != 0)
    {
        for (int i = 0; i < num; i++)
        {
            if (father[b] == array[i])//找到最近公共祖先
                goto OUT;
        }
        b = father[b];
    }
OUT:
    return father[b];
}

int main()
{
    int a, b, T;
    scanf("%d", &T);
    while (T--)
    {
        node *root = CreateTree();
        scanf("%d %d", &a, &b);
        printf("%d\n", LeastCommonAncestors(root, a, b));
        Del(root);
    }
    return 0;
}
/*
2
8 5 1 0 6 0 2 0 0 3 4 0 0 7 0 0 0
1 2
8 5 1 0 6 0 2 0 0 3 4 0 0 7 0 0 0
2 4
5
8
*/