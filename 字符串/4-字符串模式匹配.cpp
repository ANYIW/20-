#include <iostream>
#include <string>
using namespace std;
//失败函数
void Fail(string p, int *f)
{
    //初始化
    f[0] = -1;
    int k = -1;
    //填下标为j的位置
    for (int j = 1; j < p.length(); j++)
    {
        while (k >= 0 && p[k + 1] != p[j])
            k = f[k];//找更短的前缀
        if (p[k + 1] == p[j])
            k++;
        f[j] = k;
    }
}
int KMP(string s, string p, int *f)
{
    int i = 0, j = 0;
    while (i < s.length() && j < p.length())
    {
        if (s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            if (j == 0)
                i++;
            else
                j = f[j - 1] + 1;
        }
    }
    if (j == p.length())
        return i - p.length();
    return -1;
}
int main()
{
    int f[100000];
    string s, p;
    cin >> s >> p;
    Fail(p, f);
    for (int i = 0; i < p.length(); i++)
        cout << f[i] << ' ';
    cout << '\n'
         << KMP(s, p, f);
    return 0;
}