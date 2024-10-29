#include<stdio.h>
int main (void)
{
    int n, m, x;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        a[i] = x;
    }
    scanf("%d", &m);
    int b[m];
    for (int i = 0; i < m; i ++)
    {
        scanf("%d", &x);
        b[i] = x;
    }
    if (n < m)
    {
        for (int i = 0; i < n; i ++)
        {
            printf("%d %d ", a[i], b[i]);
        }
        for(int i = n; i < m; i ++)
        {
            printf("%d ", b[i]);
        }
    }
    else
    {
        for (int i = 0; i < m; i ++)
        {
            printf("%d %d ", a[i], b[i]);
        }
        for(int i = m; i < n; i ++)
        {
            printf("%d ", a[i]);
        }
    }
}