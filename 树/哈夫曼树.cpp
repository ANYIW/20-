#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node *Ptr;
struct Node
{
    char data; //非叶结点data=='#'
    int weight;
    int flag; //标记是左结点还是右结点，根结点flag==2
    Ptr left;
    Ptr right;
    Ptr father;
};
Ptr tree[1000000]; //按weight非递减排序
int begin = 0;     //tree中有效元素起始下标
int num = 0;       //tree中结点数
int count[26];     //统计字母出现次数
int collected[26]; //初始化tree时每个字母只加入一次
int WPL = 0;
//哈夫曼树根
Ptr Huffman(char *str, int len)
{
    //初始化count数组
    for (int i = 0; i < len; i++)
        count[str[i] - 'a']++;
    //初始化tree数组
    for (int i = 0; i < len; i++)
    {
        if (collected[str[i] - 'a'] == 0 && count[str[i] - 'a'])
        {
            collected[str[i] - 'a'] = 1;
            Ptr node = (Ptr)malloc(sizeof(struct Node));
            node->data = str[i];
            node->weight = count[str[i] - 'a'];
            node->left = node->right = NULL;
            node->father = NULL;
            //从后往前扫描，插在tree[j]
            //不取等，单结点优先
            int j;
            for (j = begin + num; j >= begin + 1 && tree[j - 1]->weight > node->weight; j--)
                tree[j] = tree[j - 1];
            tree[j] = node;
            num++;
        }
    }
    //构造Huffman树
    while (num >= 2)
    {
        //挑出头两个weight最小的结点构造新结点
        Ptr node = (Ptr)malloc(sizeof(struct Node));
        node->data = '#'; //标记非叶结点
        node->weight = tree[begin]->weight + tree[begin + 1]->weight;
        node->flag = 2;
        WPL += tree[begin]->weight + tree[begin + 1]->weight;
        node->left = tree[begin];
        node->right = tree[begin + 1];
        node->father = NULL;
        tree[begin]->father = node;
        tree[begin]->flag = 0;
        tree[begin + 1]->father = node;
        tree[begin + 1]->flag = 1;
        begin += 2;
        num -= 2;
        //从后往前扫描，插在tree[j]
        //不取等，单结点优先
        int j;
        for (j = begin + num; j >= begin + 1 && tree[j - 1]->weight > node->weight; j--)
            tree[j] = tree[j - 1];
        tree[j] = node;
        num++;
    }
    return tree[begin];
}
//按出现次数非递减输出编码
void Print()
{
    int i = 0;   //遍历tree
    int num = 0; //统计出现的字母数
    int stack[5000];
    int top = -1;
    for (int j = 0; j < 26; j++)
    {
        if (collected[j])
            num++;
    }
    for (int k = 0; k < num; i++)
    {
        if (tree[i]->data != '#')
        {
            k++;
            printf("%c:", tree[i]->data);
            stack[++top] = tree[i]->flag;
            Ptr tmp = tree[i]->father;
            while (tmp->flag != 2)
            {
                stack[++top] = tmp->flag;
                tmp = tmp->father;
            }
            while (top != -1)
                printf("%d", stack[top--]);
            printf("\n");
        }
    }
}
void Decode(char *str, Ptr root)
{
    int len = strlen(str);
    Ptr curr = root;
    int queue[5001]; //保存译码结果
    int front = 0;
    int rear = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->data != '#')
        {
            queue[++rear] = curr->data;
            curr = root; //译出一个字符，回到树根
        }
    }
    if (curr != root)
        printf("INVALID\n");
    else
    {
        while (front != rear)
            printf("%c", queue[++front]);
        printf("\n");
    }
}
int main()
{
    char str[5001];
    scanf("%s", str);
    int len = strlen(str); //压缩前所占字节数
    Ptr root = Huffman(str, len);
    int after = WPL / 8; //压缩后所占字节数
    if (WPL % 8)
        after++; //不足8位也算1字节
    printf("%d %d\n", len, after);
    Print();
    scanf("%s", str);
    Decode(str, root);
    scanf("%s", str);
    Decode(str, root);
    return 0;
}
/*
cbaxyyzz
0100
011
8 3  
c:100
b:101
a:110
x:111
y:00 
z:01 
zy
INVALID

uznqtanmxjd
01111001110
00101010011
11 5
u:1100
z:1101
q:1110
t:1111
a:000
m:001
j:011
n:101
juq
INVALID

ognwspggiyqnbtbv
1100011000010111
0110110110000001
16 7
o:0110
w:0111
s:1000
p:1001
i:1010
y:1011
q:1100
t:1101
v:000
n:001
b:010
g:111
INVALID
INVALID*/