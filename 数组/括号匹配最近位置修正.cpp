//在最近位置补括号
#include <stdio.h>
char str[200000];
char revise[2000000]; //修正后的括号序列
int main()
{
    int i = 0;     //str下标
    int j = 0;     //revise下标
    int left = 0;  //待匹配左括号数
    int right = 0; //待匹配右括号数
    int begin = 0; //当前括号段在str中的起始位置
    int count = 0; //需要添补的括号数
    while (scanf("%s", str) != EOF)
    {
        while (str[i] != '\0')
        {
            while (str[i] != '\0')
            {
                if (str[i] == '(')
                {
                    if (i != 0 && str[i - 1] == ')')
                        break;
                FLAG:
                    left++;
                    i++;
                }
                else if (str[i] == ')')
                {
                    right++;
                    i++;
                }
            }
            for (int k = 0; k < right - left; k++)
            {
                revise[j++] = '(';
                count++;
            }
            //str[i]=='\0'或)(中的(
            for (int k = begin; k < i; k++)
                revise[j++] = str[k];
            for (int k = 0; k < left - right; k++)
            {
                revise[j++] = ')';
                count++;
            }
            //重置
            left = 0;
            right = 0;
            begin = i;
            if (str[i] == '(')
                goto FLAG;
        }
        //输出
        if (count)
        {
            printf("%d\n", count);
            for (int k = 0; k < j; k++)
                printf("%c", revise[k]);
            printf("\n");
        }
        else
            printf("Match\n");
        //重置
        i = 0;
        j = 0;
        begin = 0;
        count = 0;
    }
    return 0;
}
/*
()())
1     
()(())

(
1 
()

)
1 
()

)(
2
()()*/