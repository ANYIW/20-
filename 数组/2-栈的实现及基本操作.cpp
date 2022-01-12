#include <stdio.h>
#include <stdlib.h>
typedef struct Stack* Ptr;
struct Stack{
    int data[20000];
    int top;
};
Ptr Create(){
    Ptr tmp=(Ptr)malloc(sizeof(struct Stack));
    tmp->top=-1;
    return tmp;
}
void Push(Ptr p,int d){
    /*if(p->top==19999){
        printf("invalid\n");
        return;
    }*/
    p->data[++p->top] = d;
    return;
}
int Pop(Ptr p){
    if(p->top==-1){
        return -1;
    }
    else{
        return p->data[p->top--];
    }
}
int main(){
    Ptr stack=Create();
    int n;
    scanf("%d",&n);
    int order;
    for(int i=0;i<n;i++){
        scanf("%d",&order);
        if(order==1){
            int d;
            scanf("%d",&d);
            Push(stack,d);
        }
        else{
            if(order==0){
                int pop=Pop(stack);
                if(pop==-1)
                printf("invalid\n");
                else printf("%d\n",pop);
            }
        }
    }
    return 0;
}