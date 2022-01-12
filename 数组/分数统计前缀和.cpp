#include <stdio.h>
#include <stdlib.h>
int a[100001]; //每个学生的分数，下标为学号，之后要按学号输出
int b[1001];  //每个分数段有多少人
int c[1001];  //每个分数之前有多少人
int main(){
    int n;
    int score;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&score);
        a[i]=score;
        b[score]++;
    }
    //c[0]==0;
    for(int i=1;i<1001;i++){
        c[i]=c[i-1]+b[i-1];
    }
    for(int i=1;i<=n;i++){
        printf("%d ",c[a[i]]);
    }
    return 0;
}