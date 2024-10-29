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
    i = i - 1;
    for (int j = 0; j <= i; j = j + 2)
    {
        printf("%d ", a[j]);
    }
    if (i % 2 == 0)
    {
        i = i - 1;
    }
    for (int j = i; j >= 0; j = j - 2)
    {
        printf("%d ", a[j]);
    }
}