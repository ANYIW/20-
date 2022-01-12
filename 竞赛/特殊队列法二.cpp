#include <stdio.h>
#include <string.h>
struct Elem
{
    int data;  //元素值
    int index; //在原队列的下标
};
struct Elem increase[2000001]; //单调递增队列，从下标为1开始存
struct Elem decrease[2000001]; //单调递减队列，从下标为1开始存
int queue[2000001];            //原队列，从下标为1开始存
int main()
{
    int T, n;      //组数，每组操作次数
    char order[8]; //操作名称
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        //Reset
        int front = 0; //指向有效元素前一个位置
        int front1 = 0;
        int front2 = 0;
        int rear = 0;  //原队列
        int rear1 = 0; //增
        int rear2 = 0; //减
        int flag = 0;  //flag==1时处于翻转状态

        for (int i = 0; i < n; i++)
        {
            scanf("%s", order);
            if (strcmp(order, "ENQUEUE") == 0)
            {
                int tmp;
                scanf("%d", &tmp);
                //原
                queue[++rear] = tmp;
                //翻转状态检测
                if (flag == 1)
                    tmp *= (-1);
                //增
                while (rear1 != front1 && increase[rear1].data >= tmp) //注意队列空的条件，不要写错成rear1!=0
                    rear1--;
                rear1++;
                increase[rear1].data = tmp;
                increase[rear1].index = rear;
                //减
                while (rear2 != front2 && decrease[rear2].data <= tmp) //注意队列空的条件，不要写错成rear2!=0
                    rear2--;
                rear2++;
                decrease[rear2].data = tmp;
                decrease[rear2].index = rear;
            }
            else if (strcmp(order, "REVERSE") == 0)
            {
                if (flag)
                    flag = 0;
                else
                    flag = 1;
            }
            else if (strcmp(order, "MAXIMUM") == 0)
            {
                if (front == rear) //队列空则不进行操作
                    continue;
                //不在翻转状态，取decrease头元素
                //翻转状态，取increase头元素的相反数
                if (flag == 0)
                {
                    printf("%d\n", decrease[front2 + 1].data);
                }
                else
                {
                    printf("%d\n", increase[front1 + 1].data * (-1));
                }
            }
            else if (strcmp(order, "DEQUEUE") == 0)
            {
                //检查index来判断单调队列是否需要出队
                if (front != rear)
                { //队列非空
                    front++;
                    if (increase[front1 + 1].index == front)
                        front1++;
                    if (decrease[front2 + 1].index == front)
                        front2++;
                }
            }
        }
        //每组数据还得再空一行
        if (T)
            printf("\n");
    }
    return 0;
}