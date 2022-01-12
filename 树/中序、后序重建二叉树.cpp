#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node* Ptr;
struct Node{
    char data;
    Ptr left;
    Ptr right;
};
//中序序列、后序序列、中序起始下标、后序起始下标、处理序列长度
Ptr PostIn(const char* in,const char* post,int in1,int post1,int len){
    //递归出口
    if(len==0)
    return NULL;
    //找post最后一个元素在in中的位置
    int k;
    int leftLen=0;//左子树序列长度
    for(k=in1;k<in1+len&&post[post1+len-1]!=in[k];k++)
    leftLen++;
    //找不到证明序列不合法
    if(k==in1+len){
        Ptr invalid=(Ptr)malloc(sizeof(struct Node));
        invalid->data='#';
        invalid->left=NULL;
        invalid->right=NULL;
        return invalid;
    }
    //构建树结点
    Ptr node=(Ptr)malloc(sizeof(struct Node));
    node->data=post[post1+len-1];
    node->left=PostIn(in,post,in1,post1,leftLen);
    node->right=PostIn(in,post,k+1,post1+leftLen,len-leftLen-1);
    return node;
}
//求高度
int Height(Ptr node,int level){
    //递归出口
    if(node==NULL)
    return level;
    //合法检测
    if(node->data=='#')
    return -1;
    //返回左右子树高度较大者
    int left=Height(node->left,level+1);
    int right=Height(node->right,level+1);
    //合法检测
    if(left==-1||right==-1)
    return -1;
    return (left>right)?left:right;
}
//先序遍历
void Pre(Ptr node){
    //递归出口
    if(node==NULL)
    return;
    //合法检测
    if(node->data=='#'){
        printf("INVALID\n");
        return;
    }
    //访问
    printf("%c",node->data);
    Pre(node->left);
    Pre(node->right);
}
//释放
void Release(Ptr node){
    //递归出口
    if(node==NULL)
    return;
    //后序遍历
    Release(node->left);
    Release(node->right);
    free(node);
}
int main(){
    char in[27];
    char post[27];
    while(scanf("%s",post)!=EOF){
        scanf("%s",in);
        //长度不等导致不合法
        if(strlen(in)!=strlen(post)){
            printf("INVALID\n");
            continue;
        }
        int len=strlen(in);
        Ptr root=PostIn(in,post,0,0,len);
        int height=Height(root,-1);
        //排列不合法
        if(height==-1){
            printf("INVALID\n");
            continue;
        }
        printf("%d\n",height);
        Pre(root);
        Release(root);
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