#include <stdio.h>
#include <string.h>
int last['z'];//每个字母在str中最后出现的位置
int app['z'];//每个字母是否出现
int num[2000];//位置i及其之后不重复字符个数
int main(){
    char str[2000];
    int n=strlen(str);
    for(int i=0;i<n;i++)
    last[str[i]]=i;
    //从后往前递推
    for(int i=n-1;i>=1;i--){
        if(app[str[i]]==0){
            num[i-1]=num[i]+1;
            app[str[i]]=1;
        }
        else num[i-1]=num[i];
    }
    return 0;
}