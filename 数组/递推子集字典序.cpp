#include <stdio.h>
int orange[100];
void Print(int curr)
{
    for (int i = 1; i <= curr; i++)
    {
        if (i == 1)
            printf("{%c", 'a' + orange[i] - 1);
        else
            printf(",%c", 'a' + orange[i] - 1);
    }
    printf("}\n");
}
int main()
{
    int n;
    int curr = 0; //有效元素下标从1开始
    //orange[curr] = 0;
    scanf("%d", &n);
    printf("{}\n");
    while (orange[1] != n)
    {
        if (orange[curr] < n)
        {
            orange[curr + 1] = orange[curr] + 1;
            curr++;
        }
        else if (curr != 1)
        { //curr!=1 && orange[curr]==n
            curr--;
            orange[curr] += 1;
        }
        else
        { //orange[1]==n
            Print(curr);
            break;
        }
        Print(curr); //打印每次递推结果
    }
    return 0;
}
/*
3
{}
{a}
{a,b}
{a,b,c}
{a,c}
{b}
{b,c}
{c}

4
{}     
{a}    
{a,b}  
{a,b,c}
{a,b,c,d}
{a,b,d}
{a,c}
{a,c,d}
{a,d}
{b}
{b,c}
{b,c,d}
{b,d}
{c}
{c,d}
{d}*/