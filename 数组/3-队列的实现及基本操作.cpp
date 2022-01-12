#include <stdio.h>
#include <stdlib.h>
typedef struct Queue* Ptr;
struct Queue{
    int data[20001];//总共能存20000个数
    int front,rear;//front指向有效元素前一个位置
};
Ptr Create(){
    Ptr tmp=(Ptr)malloc(sizeof(struct Queue));
    tmp->front=tmp->rear=0;
    return tmp;
}
void Add(Ptr p,int d){
    if ((p->rear + 1) % 20001 == p->front)
    return;//队列满
    p->rear=(p->rear+1)%20001;
    p->data[p->rear]=d;
    return;
}
int Delete(Ptr p){
    if(p==NULL||p->front==p->rear)
    return -1;//队列空
    p->front=(p->front+1)%20001;
    return p->data[p->front];
}
int main(){
    Ptr queue=Create();
    int n;
    scanf("%d",&n);
    int order;
    for(int i=0;i<n;i++){
        scanf("%d",&order);
        if(order==1){
            int d;
            scanf("%d",&d);
            Add(queue,d);
        }
        else{
            if(order==0){
                int result=Delete(queue);
                if(result==-1)
                printf("invalid\n");
                else printf("%d\n",result);
            }
        }
    }
    free(queue);
    return 0;
}