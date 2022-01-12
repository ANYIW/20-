#include <stdio.h>
const int ERROR = -1;
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
int ancestor1[1000];
int num1 = 0;
//寻找以root为根的子树中的target结点，填写经过的祖先
//返回是否找到
int Pre(node *root, int target)
{
    if (root == NULL)
        return false;
    ancestor1[num1++] = root->data;
    if (root->data == target)
        return true;
    node *tmp = root->firstChild;
    while (tmp)
    {
        int flag = Pre(tmp, target);
        if (flag)
            return true;
        //能运行到这说明当前tmp子树中找不到target，丢弃tmp，寻找其兄弟
        num1--;
        tmp = tmp->nextBrother;
    }
    return false;
}
/* 你的代码将出现在这里 */
int LeastCommonAncestors(node *root, int a, int b)
{
    //暂存到a所经过的祖先
    int ancestor2[1000];
    int num2 = 0;
    //递归先序遍历
    if (Pre(root, a) == 0)
        return ERROR;
    for (int i = 0; i < num1; i++)
        ancestor2[num2++] = ancestor1[i];
    num1 = 0;

    if (Pre(root, b) == 0)
        return ERROR;
    //逐一比较
    for (int i = num1 - 1; i >= 0; i--)
    {
        for (int j = num2 - 1; j >= 0; j--)
        {
            if (ancestor1[i] == ancestor2[j])
                return ancestor1[i];
        }
    }
    return ERROR;
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