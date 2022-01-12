#include <stdio.h>
#include <stdlib.h>
typedef struct Node *Ptr;
struct Node
{
    int data;
    int flag; //flag==1则在队列，flag==0则已出队
    Ptr last; //逆时针
    Ptr next; //顺时针
};
int main()
{
    int n, m, k;
    int out = 0; //当前出队的人数
    scanf("%d%d%d", &n, &m, &k);
    //创建双向循环链表
    Ptr head = (Ptr)malloc(sizeof(struct Node));
    head->data = 1;
    head->flag = 1;
    head->last = head->next = NULL;
    Ptr tail = head;
    for (int i = 2; i <= n; i++)
    {
        Ptr tmp = (Ptr)malloc(sizeof(struct Node));
        tmp->data = i;
        tmp->flag = 1;
        tmp->last = tail;
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
    }
    head->last = tail;
    tail->next = head;

    while (1)
    {
        //逆时针报数m次
        int count = 0;
        while (1)
        {
            if (head->flag == 1)
                count++;    //报数
            if (count == m) //及时退出循环
                break;
            head = head->last;
        }
        printf("%d ", head->data);
        head->flag = 0; //出队
        out++;
        if (out == n)
            break;
        //逆时针寻找下一次开始报数的人
        while (head->flag == 0)
            head = head->last;

        //顺时针报数k次
        count = 0;
        while (count != k)
        {
            if (head->flag == 1)
                count++;    //报数
            if (count == k) //及时退出循环
                break;
            head = head->next;
        }
        printf("%d ", head->data);
        head->flag = 0; //出队
        out++;
        if (out == n)
            break;
        //顺时针寻找下一次开始报数的人
        while (head->flag == 0)
            head = head->next;
    }
    return 0;
}
/*
6 3 5
5 3 1 2 4 6*/