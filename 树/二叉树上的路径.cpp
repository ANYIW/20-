#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node
{
    int data;
    Ptr left,right;
};
Ptr Create(){
    int tmp;
    scanf("%d",&tmp);
    if(tmp==0)
    return NULL;
    Ptr node=(Ptr)malloc(sizeof(struct Node));
    node->data=tmp;
    node->left=Create();
    node->right=Create();
    return node;
}
int FindPath(Ptr node,int* path,int* len,int curr,int target){
    if(node==NULL)
    return 0;
    path[curr]=node->data;
    (*len)=curr;
    if(target==node->data)
        return 1;
    if(FindPath(node->left,path,len,curr+1,target))
    return 1;
    return FindPath(node->right,path,len,curr+1,target);

}
void LeastCommonAncestor(Ptr root,int a,int b){
    int len1=0,len2=0;
    int path1[6000];
    int path2[6000];
    FindPath(root,path1,&len1,0,a);
    FindPath(root,path2,&len2,0,b);
    int i;
    for(i=0;path1[i+1]==path2[i+1];i++);
    printf("%d",len1+len2-2*i);
}
int main(){
    Ptr root=Create();
    int a,b;
    scanf("%d%d",&a,&b);
    LeastCommonAncestor(root,a,b);
    return 0;
}
/*
1 2 9 0 0 0 3 5 7 0 0 8 0 0 6 0 0
7 8
2

1 2 9 0 0 0 3 5 7 0 0 8 0 0 6 0 0
7 6
3*/