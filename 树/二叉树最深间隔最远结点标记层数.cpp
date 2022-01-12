#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node{
    int data;
    int level;
    Ptr left;
    Ptr right;
};
int deepest=-1;
Ptr Create(int currLevel){
    int d;
    scanf("%d",&d);
    //出口
    if(d==0)
    return NULL;
    //创建
    if (currLevel > deepest)
        deepest = currLevel;
    Ptr node=(Ptr)malloc(sizeof(struct Node));
    node->data=d;
    node->level=currLevel;  
    node->left=Create(currLevel+1);
    node->right=Create(currLevel+1);
    return node;
}
int times = 1; //首次访问最深层首结点
int first,last;//最深层首尾结点值
void PreOrder(Ptr node){
    //出口
    if(node==NULL)
    return;
    if(node->level==deepest&&times==1){
        first=node->data;
        times++;
    }
    if(node->level==deepest)
    last=node->data;
    //先序
    PreOrder(node->left);
    PreOrder(node->right);
}
int main(){
    Ptr root=Create(0);
    PreOrder(root);
    if(last-first>=0)
    printf("%d",last-first);
    else printf("%d",(-1)*(last-first));//输出绝对值
    return 0;
}