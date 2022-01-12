#include <stdio.h>
#include <string.h>
char str[100010];
int fail[100010]; //失败函数
int Fail(int len)
{
    int max = -1;
    int k = -1;
    fail[0] = -1;
    int j;
    for (j = 1; j < len; j++)
    {
        while (k >= 0 && str[k + 1] != str[j])
            k = fail[k];
        if (str[k + 1] == str[j])
            k++;
        fail[j] = k;
        //更新最大值
        if (fail[j] > max)
            max = fail[j];
    }
    return max;
}
int main()
{
    int len; //字符串长度
    int max; //失败函数最大值
    int second = 0;
    while (scanf("%s", str)!=EOF)
    {
        len = strlen(str);
        second = 0; //假设不存在第二长相等前后缀
        Fail(len);
        if (fail[len - 1] >= 0)
            second = fail[fail[len - 1]] + 1;
        int Q=len-2*second;
        if(Q<0)
        Q=0;
        //翻转字符串
        char str2[100010];
        for (int i = 0; i < len / 2; i++)
        {
            char tmp = str[i];
            str[i] = str[len - 1 - i];
            str[len - 1 - i] = tmp;
        }
        max = Fail(len);
        //printf("%d\n", max + 1);
        //printf("%d\n", second);
        //printf("%d\n", len - 2 * second);
        printf("%d\n", max + 1 + Q);
    }
    return 0;
}