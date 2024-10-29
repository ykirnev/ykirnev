#include <stdio.h>

int main(void)
{
    int a[10000];
    int x;
    scanf("%d", &x);
    a[0] = x;
    int i = 1;
    while (x != 0)
    {
        scanf("%d", &x);
        a[i] = x;
        i ++;
    }
    int s = a[0];
    int j = 1;
    if (i % 2 == 0)
    {
        while (j < i)
        {
              s = s + a[j] * a[j + 1];
              j = j + 2;
        } 
    }
    else{
        s = s + a[i - 2];
        while(j < i)
        {
             s = s + a[j] * a[j + 1];
              j = j + 2;
        } 
    }
    printf("%d", s);
    return 0;
}