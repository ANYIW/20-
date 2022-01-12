#include <stdio.h>
int f[1000010];
void Fail(const char *str, int n)
{
    int i = -1;
    f[0] = -1;
    for (int j = 1; j < n; j++)
    {
        while (i >= 0 && str[i + 1] != str[j])
            i = f[i];
        if (str[i + 1] == str[j])
            i++;
        f[j] = i;
    }
}
int main()
{
    int n;
    long long result = 0;
    char str[1000010];
    scanf("%d%s", &n, str);
    Fail(str, n);
    //累加所有前缀的秩之和
    for (int i = 0; i < n; i++)
    {
        //若不存在相等的前后缀，则秩为0，不累加
        if (f[i] >= 0)
        {
            int tmp = f[i];
            //寻找最短相等前后缀的下标
            while (f[tmp] >= 0)
            {
                tmp = f[tmp];
            }
            //f递推地保存最短相等前后缀下标，以减少后序迭代次数
            f[i]=tmp;
            result += i - tmp;
        }
    }
    printf("%lld", result);
    return 0;
}