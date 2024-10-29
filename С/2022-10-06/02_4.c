#include<stdio.h>

int mx(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}
int main(void)
{
    unsigned int n, ans = 0;
    scanf("%u", &n);
    unsigned int x1[n];
    unsigned int x2[n];
    for (int i = 0; i < n; i ++)
    {
        scanf("%u", &x1[i]);
    }
    for (int i = 0; i < n; i ++)
    {
        scanf("%u", &x2[i]);
    }
    for (int i = 0; i < n; i ++)
    {
        ans = ans + mx(x1[i], x2[i]);
    }
    printf("%u", ans);
}