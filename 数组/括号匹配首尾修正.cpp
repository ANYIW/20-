//可以不用栈
#include <stdio.h>
char str[200000];
char stack[200000];
int main()
{
    int top = -1;
    int i = 0; //遍历str
    while (scanf("%s", str) != EOF)
    {
        while (str[i] != '\0')
        {
            if (str[i] == '(')
                stack[++top] = str[i];
            else if (str[i] == ')')
            {
                if (top == -1 || stack[top] == ')') //匹配不成功则压栈
                    stack[++top] = str[i];
                else if (stack[top] == '(') //弹出匹配成功的括号对
                    top--;
            }
            i++;
        }
        if (top == -1)
            printf("Match\n");
        else
        {
            int left = 0;  //栈中左括号数
            int right = 0; //栈中右括号数
            while (top != -1)
            {
                if (stack[top] == '(')
                    left++;
                else
                    right++;
                top--;
            }
            printf("%d\n", left + right);
            //未不匹配的右括号数需要添左括号来匹配
            for (int j = 0; j < right; j++)
                printf("(");
            for (int j = 0; j < i; j++)
                printf("%c", str[j]);
            //未匹配的左括号需要添右括号来匹配
            for (int j = 0; j < left; j++)
                printf(")");
            printf("\n");
        }
        //重置
        top = -1;
        i = 0;
    }
    return 0;
}