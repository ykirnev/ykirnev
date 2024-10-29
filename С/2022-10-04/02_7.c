#include <stdio.h>
int main(void)
{
    int n, x;
    scanf("%d", &n);
    int a[n], b[n];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        a[i] = x;
    }
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        b[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if ((a[i] <= n) && (a[i] > 0))
        {
            b[a[i] - 1]++;
        }
        else
        {
            flag = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (b[i] != 1)
        {
            flag = 0;
        } 
    }
    if (flag == 1)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }





}