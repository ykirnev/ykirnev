#include<stdio.h>
int main(void)
{
    unsigned int n, x, xr, xr_2;
    scanf("%d", &n);
    unsigned int a[n];
    scanf("%d", &x);
    xr = x;
    a[0] = x;
    for (int i = 1; i < n; i ++ )
    {
        scanf("%d", &x);
        a[i] = x;
        xr = xr ^ x;
    }
    unsigned int mask = 0;
    for (int i = 31; i >= 0; i--)
    {
        mask = 1 << i;
        if ((mask & xr) != 0)
        {
            break;
        }
    }
    xr_2 = 0;
    for (int i = 0; i < n; i++)
    {
        if ((mask & a[i]) != 0)
        {
            xr_2 = xr_2 ^ a[i];
        }
    }
    unsigned int ans_1 = xr_2;
    unsigned int ans_2 = xr ^ xr_2;
    if (ans_1 > ans_2)
    {
        x = ans_1;
        ans_1 = ans_2;
        ans_2 = x;
    }
    printf("%u %u", ans_1, ans_2);
}