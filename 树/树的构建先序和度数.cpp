#include <stdio.h>
#include <stdlib.h>
typedef struct Info *PtrI;
struct Info
{
    char data;
    int degree; //度数
};
struct Info information[12] = {{'A', 4}, {'B', 0}, {'C', 3}, {'G', 0}, {'H', 2}, {'D', 0}, {'E', 0}, {'F', 0}, {'I', 2}, {'L', 0}, {'J', 0}, {'K', 0}};
typedef struct Node *PtrT;
struct Node
{
    char data;
    PtrT leftSon;
    PtrT rightBro; //brother
};
//打印树的先序序列
void PrintPre(PtrT root)
{
    if (root == NULL)
    {
        //printf("%c", '#');树的子结点数不确定，所以不能用'#'表示空结点
        return;
    }
    printf("%c", root->data);
    PrintPre(root->leftSon);
    PrintPre(root->rightBro);
}
//求树的高度
int Height(PtrT root)
{
    if (root == NULL)
        return -1;
    PtrT child = root->leftSon;
    int max = 0;
    //从第一棵子树开始向右递归更新高度
    while (child)
    {
        int level = Height(child) + 1;
        if (level > max)
            max = level;
        child = child->rightBro;
    }
    return max;
}
//查找树中某结点的父结点
void FindFather(PtrT root, PtrT node, PtrT *result)
{
    if (root == NULL || node == NULL || root == node)
        (*result) = NULL;
    //判断root和node是否互为兄弟
    PtrT tmp = root->rightBro;
    while (tmp)
    {
        if (tmp == node)
        {
            (*result) = NULL;
            return;
        }
        tmp = tmp->rightBro;
    }
    //从第一棵子树开始搜索，搜索到则返回，否则搜索下一棵子树
    tmp = root->leftSon;
    while (tmp)
    {
        if (tmp == node)
            (*result) = root;
        FindFather(tmp, node, result);
        if (result)
            return;
        tmp = tmp->rightBro;
    }
}
//根据层序序列和结点度数构建树，假设给定的Information数组合法
PtrT queue[100]; //存各结点的地址
PtrT CreateLevel(PtrI info)
{
    int pointer = 0; //遍历info数组
    int curr=0;//指向当前出队结点对应的info
    int front = 0;
    int rear = 0;
    PtrT root = (PtrT)malloc(sizeof(struct Node));
    root->data = info[curr].data;
    root->leftSon = root->rightBro = NULL;
    queue[++rear] = root;//第一个结点入队

    while (front != rear)
    {
        PtrT out = queue[++front]; //出队
        if (info[curr].degree)
        { //创建第一个儿子
            pointer++;
            out->leftSon = (PtrT)malloc(sizeof(struct Node));
            out->leftSon->data = info[pointer].data;
            out->leftSon->leftSon = out->leftSon->rightBro = NULL;
            queue[++rear]=out->leftSon;//创建一个结点就入队
        }
        PtrT child = out->leftSon;
        for (int i = 1; i < info[curr].degree; i++)
        { //创建之后的儿子
            pointer++;
            child->rightBro = (PtrT)malloc(sizeof(struct Node));
            child->rightBro->data = info[pointer].data;
            child->rightBro->leftSon = child->rightBro->rightBro = NULL;
            child = child->rightBro;//往右走
            queue[++rear] = child;  //创建一个结点就入队
        }
        curr++;
    }
    return root;
}
int main()
{
    PtrT tree = CreateLevel(information);
    printf("PreOrder:");
    PrintPre(tree);
    printf("\nHeight:%d",Height(tree));
    return 0;
}
/*
ABCDEFGHIJKL*/