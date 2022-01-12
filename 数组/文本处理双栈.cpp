#include <stdio.h>
char stack1[50000]; //光标前
char stack2[50000]; //光标后
int main()
{
    int top1 = -1;
    int top2 = -1;
    int flag = 0; //插入为0，覆盖为1
    char ch = getchar();
    while (ch != '\n')
    {
        switch (ch)
        {
        case 'k':
            //光标左移：stack1弹出一个字符压入stack2
            if (top1 != -1)
                stack2[++top2] = stack1[top1--];
            break;
        case 'z':
            //光标右移：stack2弹出一个字符压入stack1
            if (top2 != -1)
                stack1[++top1] = stack2[top2--];
            break;
        case 'w':
            //光标移到文档头：stack1全部字符弹出并压入stack2
            while (top1 != -1)
                stack2[++top2] = stack1[top1--];
            break;
        case 's':
            //光标移到文档尾：stack2全部字符弹出并压入stack1
            while (top2 != -1)
                stack1[++top1] = stack2[top2--];
            break;
        case 'q':
            //删除光标前一个字符：stack1不空则弹出一个字符
            if (top1 != -1)
                top1--;
            break;
        case 'm':
            if (flag)
                flag = 0;
            else
                flag = 1;
            break;
        default:
            if (flag == 0) //插入
                stack1[++top1] = ch;
            else
            { //覆盖
                if (top2 != -1)
                    top2--;
                stack1[++top1] = ch;
            }
        }
        ch=getchar();
    }
    //将stack1中字符全部压入stack2中，再依次弹出stack2中字符
    while(top1!=-1)
    stack2[++top2]=stack1[top1--];
    while(top2!=-1)
    printf("%c",stack2[top2--]);
    return 0;
}
/*
abckd
abdc

abckkzd
abdc

abcwd
dabc

abcwdse
dabce

abcq
ab

abckmd
abd

abckkmdme
adec*/