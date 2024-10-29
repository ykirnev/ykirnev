#include<stdio.h>
int mn(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    return a;
}
int mx(int a, int b)
{
    if (a < b)
    {
        return b;
    }
    return a;
}
int med(int a, int b, int c)
{
    int maxim = mx(a, mx(b, c));
    int minim = mn(a, mn(b, c));
    return(a + b + c - maxim - minim);
}
int func(int a[], int n)
{
    if (n == 1)
    {
        return a[0];
    }
    n = n - 2;
    int b[n];
    for (int i = 0; i < n; i ++){
        b[i] = med(a[i], a[i + 1], a[i + 2]);
    }
    return(func(b, n));
}
int main(void)
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &a[i]);
    }
    printf("%d", func(a, n));
    return 0;
}