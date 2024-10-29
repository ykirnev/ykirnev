#include <stdio.h>
int main(void)
{
    int n, x;
    scanf("%d", &n);
    int a[n], b[n], c[n];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        a[i] = x;
    }
    for (int i = 0; i < n; i ++)
    {
        b[i] = a[i];
    }
    for (int i = 0; i < n; i ++)
    {
        c[i] = b[a[i] - 1];
    }
    for (int i = 0; i < n; i ++)
    {
        b[i] = c[a[i] - 1];
    }
    for (int i = 0; i < n; i ++)
    {
        printf("%d ", b[i]);
    }



}