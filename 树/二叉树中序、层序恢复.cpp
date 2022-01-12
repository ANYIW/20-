#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node *Ptr;
struct Node
{
    char data;
    Ptr left;
    Ptr right;
};
//先序遍历
void Pre(Ptr node)
{
    //递归出口
    if (node == NULL)
        return;
    //合法检测
    /*if(node->data=='#'){
        printf("INVALID\n");
        return;
    }*/
    //访问
    printf("%c", node->data);
    Pre(node->left);
    Pre(node->right);
}
int flag[26]; //大写字母'A'~'Z'状态，1：左子树未生成的结点，2：右子树未生成的结点，0：无效的结点
//中序序列、层序序列、中序序列起始下标、序列总长度、当前处理序列长度
Ptr InLevel(const char *in, const char *level, int in1, int len, int currLen, int tag)
{
    //递归出口
    if (currLen == 1)
    {
        flag[in[in1] - 'A'] = 0;
        Ptr leaf = (Ptr)malloc(sizeof(struct Node));
        leaf->data = in[in1];
        leaf->left = NULL;
        leaf->right = NULL;
        return leaf;
    }
    //找level第一个flag==tag的元素生成结点
    int i;
    for (i = 0; i < len; i++)
        if (flag[level[i] - 'A'] == tag)
            break;
    //递归出口
    if (i == len)
        return NULL;
    //找level[i]在in中的下标，计算出左子树元素个数
    int k;
    int leftLen = 0;
    for (k = in1; k < in1 + currLen && in[k] != level[i]; k++)
        if (flag[in[k] - 'A'] == tag)
            leftLen++;
    if (k == in1 + currLen)
    {
        printf("invalid\n");
        exit(0);
    }
    //左子树元素标记为1，构建左子树
    for (int j = in1; j < in1 + currLen; j++)
    {
        if (j < k)
            flag[in[j] - 'A'] = 1;
        /*if (j > k)
            flag[in[j] - 'A'] = 2;*/
    }
    flag[level[i] - 'A'] = 0;
    Ptr node = (Ptr)malloc(sizeof(struct Node));
    node->data = level[i];
    node->left = InLevel(in, level, k - leftLen, len, leftLen, 1);
    for (int j = in1; j < in1 + leftLen; j++) //恢复flag
        flag[in[j] - 'A'] = 0;
    //右子树元素标记为2，构建右子树
    for (int j = in1; j < in1 + currLen; j++)
    {
        /*if (j < k)
            flag[in[j] - 'A'] = 1;*/
        if (j > k)
            flag[in[j] - 'A'] = 2;
    }
    node->right = InLevel(in, level, k + 1, len, currLen - leftLen - 1, 2);
    for (int j = k + 1; j < len - k - leftLen; j++)
        flag[in[j] - 'A'] = 0;

    return node;
}
//释放
void Release(Ptr node)
{
    //递归出口
    if (node == NULL)
        return;
    //后序遍历
    Release(node->left);
    Release(node->right);
    free(node);
}
int main()
{
    char in[10] = "CBEDFAGH";
    char level[10] = "ABGCDHEF";
    int len = strlen(in);
    Ptr root = InLevel(in, level, 0, len, len, 0);
    Pre(root);
    Release(root);
    return 0;
}
/*ABCDEFGH*/