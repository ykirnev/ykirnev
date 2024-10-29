#include <stdio.h>

int main(void)
{
    int a[100000];
    int x, i = 0;
    scanf("%d", &x);
    while (x!= 0)
    {
        a[i] = x;
        scanf("%d", &x);
        i ++;
    }
    for (i = i - 1; i >= 0; i --)
    {
        printf("%d ", a[i]);
    }

}