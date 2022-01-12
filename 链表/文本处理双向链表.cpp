#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
typedef struct Node *Ptr;
struct Node
{
    char data;
    Ptr front;
    Ptr back;
};
//前后都有哨兵
Ptr Create()
{
    Ptr head = (Ptr)malloc(sizeof(struct Node));
    Ptr rear = (Ptr)malloc(sizeof(struct Node));
    head->data = rear->data = '\0';
    head->front = rear->back = NULL;
    head->back = rear;
    rear->front = head;
    return head;
}
void Delete(Ptr node)
{
    if (node == NULL)
        return;
    node->front->back = node->back;
    node->back->front = node->front;
    free(node);
}
//在node前增加一个结点
void Add(Ptr node, char ch)
{
    Ptr tmp = (Ptr)malloc(sizeof(struct Node));
    tmp->data = ch;
    tmp->back = node;
    tmp->front = node->front;
    node->front = tmp;
    tmp->front->back = tmp;
}
void Print(Ptr head)
{
    head = head->back; //越过哨兵
    while (head)
    {
        printf("%c", head->data);
        head = head->back;
    }
}
int main()
{
    int flag = 0; //0为插入，1为改写
    char str[50001];
    //gets_s(str,50001);
    char ch = getchar();
    int i = 0;
    while (ch != '\n')
    {
        str[i++] = ch;
        ch = getchar();
    }
    Ptr head = Create();
    Ptr rear = head->back;
    Ptr curr = rear; //光标在curr->front与curr之间
    for (int i = 0; i < strlen(str); i++)
    {
        switch (str[i])
        {
        case 'k': //往前移一位
            if (curr->front != head)
                curr = curr->front;
            break;
        case 'z': //往后移一位
            if (curr->back)//最后有哨兵
                curr = curr->back;
            break;
        case 'w': //移到文本头
            curr = head->back;
            break;
        case 's': //移到文本尾
            curr = rear;
            break;
        case 'q': //删除前一位
            if (curr->front != head)
                Delete(curr->front);
            break;
        case 'm': //插入or改写切换
            if (flag == 0)
                flag = 1;
            else
                flag = 0;
            break;
        default:
            if (flag)//覆盖
            {
                if(curr!=rear){
                    curr->data = str[i];
                    curr = curr->back; //光标需后移
                }
                else Add(curr,str[i]);//文本尾则覆盖、插入无区别
                
            }
            else//curr前插入
                Add(curr, str[i]); //光标无需移动
        }
    }
    Print(head);
    return 0;
}
/*
abckdefq sghi
abde cghi
abcwmdsef
dbcef*/