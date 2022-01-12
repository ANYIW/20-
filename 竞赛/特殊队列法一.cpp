#include <stdio.h>
#include <stdlib.h>
#include <string.h>//strcmp
#define MIN -32768//最小int
#define MAX 32767//最大int
typedef struct Queue *Ptr;
struct Queue
{
    int *data;
    int front, rear;//front下一个元素开始有效
    int capacity;
};
Ptr Create(int n)
{
    Ptr queue = (Ptr)malloc(sizeof(struct Queue));
    queue->capacity = n;
    queue->data = (int *)malloc(sizeof(int) * n);
    queue->front = queue->rear = 0;
    return queue;
}
void Add(Ptr q, int d)
{
    if (q == NULL)
        return;
    if ((q->rear + 1) % (q->capacity) == q->front)
        return;
    q->rear = (q->rear + 1) % (q->capacity);
    q->data[q->rear] = d;
}
int Delete(Ptr q)
{
    if (q == NULL || q->front == q->rear)
        return NULL;
    q->front = (q->front + 1) % (q->capacity);
    return q->data[q->front];
}
int main()
{
    int n, m; //组数、操作数
    int tmp;//暂存入队元素
    char order[8];//存操作指令
    int max=MIN;
    int min=MAX;
    Ptr queue=Create(2000000);
    scanf("%d",&n);
    while(n--){
        scanf("%d",&m);
        for(int i=0;i<m;i++){
            scanf("%s",order);
            if(strcmp(order,"ENQUEUE")==0){
                scanf("%d",&tmp);
                if(tmp>max)
                max=tmp;
                if(tmp<min)
                min=tmp;
                Add(queue,tmp);
            }
            else if(strcmp(order,"REVERSE")==0){
                int i=queue->front+1;
                while(i!=queue->rear){
                    queue->data[i]*=(-1);
                    i=(i+1)%(queue->capacity);
                }
                queue->data[i]*=(-1);//逆转队尾元素
                tmp=max;
                max=min*(-1);
                min=tmp*(-1);
            }
            else if(strcmp(order,"MAXIMUM")==0){
                if(queue->front!=queue->rear)
                printf("%d\n",max);
            }
            else if(strcmp(order,"DEQUEUE")==0){
                tmp=Delete(queue);
                if(tmp==max){
                    int i=queue->front+1;
                    max=MIN;
                    while(i!=queue->rear){
                        if(queue->data[i]>max)
                        max=queue->data[i];
                        i = (i + 1) % (queue->capacity);
                    }
                    if(queue->data[i]>max)
                    max=queue->data[i];
                }
                else if(tmp==min){
                    int i=queue->front+1;
                    min=MAX;
                    while(i!=queue->rear){
                        if(queue->data[i]<min)
                        min=queue->data[i];
                        i=(i+1)%(queue->capacity);
                    }
                    if(queue->data[i]<min)
                    min=queue->data[i];
                }
            }
        }
        //重置
        while(queue->front!=queue->rear)
        Delete(queue);
        max=MIN;
        min=MAX;
    }
    return 0;
}
/*
1
6
ENQUEUE -8
REVERSE
ENQUEUE -5
MAXIMUM
8//输出
DEQUEUE
MAXIMUM
-5//输出
*/