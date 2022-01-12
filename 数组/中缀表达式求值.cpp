#include <stdio.h>
#include <stdlib.h>
char stack1[100]; //运算符栈
int stack2[100];  //运算数栈
int Operation(int a, int b, char op)
{ //b先于a弹栈
    int result;
    switch (op)
    {
    case '+':
        result = a + b;
        break;//勿漏
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (b)
            result = a / b;
        else
        {
            printf("ILLEGAL");
            exit(0);
        }
        break;
    }
    return result;
}
int main()
{
    int top1 = -1;
    int top2 = -1;
    int isNegative = 0; //是否是负数
    char exp[100];
    int i = 0;        //遍历每个字符
    scanf("%s", exp); //比getchar快
    while (exp[i] != '\0')
    {
        if (exp[i] >= '0' && exp[i] <= '9')
        {
            int sum = 0;
            while (exp[i] >= '0' && exp[i] <= '9')
            {
                sum = sum * 10 + exp[i] - '0';
                i++;
            }
            if (isNegative)
            {
                sum *= (-1);
                isNegative = 0; //重置
            }
            stack2[++top2] = sum;
        }
        else if (exp[i] == '(' || exp[i] == '*' || exp[i] == '/')
        { //左括号直接压栈，'*'、'/'优先级最高，也直接压栈
            stack1[++top1] = exp[i];
            i++;
        }
        else if (exp[i] == ')')
        { //弹栈直至栈顶为左括号
            while (stack1[top1] != '(')
            {
                int b = stack2[top2--];
                int a = stack2[top2--];
                stack2[++top2] = Operation(a, b, stack1[top1--]);
            }
            top1--; //弹出左括号
            i++;
        }
        else if (exp[i] == '+' || exp[i] == '-')
        {
            if (exp[i] == '-')
            {
                if (i == 0 || exp[i - 1] == '(')
                { //'-'是负号
                    isNegative = 1;
                    i++;
                    continue;
                }
            }
            while (top1 != -1 && stack1[top1] != '(')
            { //'-'、'+'为运算符，则优先级最低
                int b = stack2[top2--];
                int a = stack2[top2--];
                stack2[++top2] = Operation(a, b, stack1[top1--]);
            }
            stack1[++top1] = exp[i]; //当前运算符压栈
            i++;
        }
    }
    while (top1 != -1)
    {
        int b = stack2[top2--];
        int a = stack2[top2--];
        stack2[++top2] = Operation(a, b, stack1[top1--]);
    }
    printf("%d", stack2[top2--]);
    return 0;
}
/*
5+(10*2)-6
19
8*(999+1)
8000
1+5/(1-1)
ILLEGAL*/