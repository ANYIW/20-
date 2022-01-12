+#include <stdio.h>
#include <string.h>
#define ILLEGAL -1
char pre[27];
char in[27];
char post[27];
//当前所在层数、当前处理序列长度、先序、中序、后序序列起始下标，返回高度
int PostIntoPre(int level, int len, int pre1, int in1, int post1)
{
    if (len == 0)
        return level;
    pre[pre1] = post[post1 + len - 1]; //post最后一个元素为pre第一个元素
    int k;                             //post最后一个元素在in中的下标
    int left = 0;                      //下次递归左子树的序列长度
    for (k = in1; k < in1 + len && post[post1 + len - 1] != in[k]; k++)
        left++;
    //post最后一个元素在in中找不到，证明序列不合法
    if (k == in1 + len)
        return ILLEGAL;
    //递归填充左右子树
    int height1 = PostIntoPre(level + 1, left, pre1 + 1, in1, post1);
    int height2 = PostIntoPre(level + 1, len - left - 1, pre1 + left + 1, k + 1, post1 + left);
    if (height1 == -1 || height2 == -1)
        return ILLEGAL;
    else
        return (height1 > height2) ? height1 : height2; //返回左右子树高度的较大者
}
int main()
{
    while (scanf("%s", post)!=EOF){
        scanf("%s", in);
        //长度不合法
        if (strlen(post) != strlen(in))
        {
            printf("INVALID");
            return 0;
        }
        int len = strlen(post);
        int height = PostIntoPre(-1, len, 0, 0, 0);
        if (height != ILLEGAL)
        {
            printf("%d\n", height);
            printf("%s\n", pre);
        }
        else
            printf("INVALID\n");
    }
    return 0;
}
/*
CEFDBHGA
CBEDFAGH
3
ABCDEFGH

CBEDFAGH
CEFDBHGA
INVALID

BCA
CAB
INVALID*/