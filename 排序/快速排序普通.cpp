#include <stdio.h>
int a[1000];
void Swap(int i,int j){
    if(i==j)
    return;
    int tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
}
void Print(int n){
    for(int i=0;i<n;i++)
    printf("%d ",a[i]);
    printf("\n");
}
void Quick(int n,int begin,int end){
    if(begin>=end)
    return;
    int i=begin+1,j=end;
    while(1){
        while(i<=end&&a[i]<=a[begin])
        i++;
        while(a[j]>a[begin])
        j--;
        if(i<j)
        Swap(i,j);
        else break;
    }
    Swap(begin,j);
    Print(n);
    Quick(n,begin,j-1);
    Quick(n,j+1,end);
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    scanf("%d",&a[i]);
    Quick(n,0,n-1);
    Print(n);
    return 0;
}
/*
5
4 5 3 2 1
2 1 3 4 5 
1 2 3 4 5 
1 2 3 4 5*/