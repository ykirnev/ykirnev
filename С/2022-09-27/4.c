#include <stdio.h>

int main (void)
{
    int n, x;
    scanf("%d", &n);
    int m[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        m[i] = x;
    }
    int min = 1000000000;
    int max = 0;
    int min_i = 0;
    int max_i = 0;
    for (int i = 0; i < n; i++)
    {
        if (min > m[i])
        {
            min = m[i];
            min_i = i;
        }
        if (max < m[i])
        {
            max = m[i];
            max_i = i;
        }
    }
    int change;
    if (max_i < min_i)
    {
        change = max_i;
        max_i = min_i;
        min_i = change;
    }
    for (int i = min_i; i <= (max_i - ((max_i - min_i) / 2) - (max_i - min_i) % 2); i ++)
    {
        change = m[i];
        m[i] = m[max_i - i + min_i];
        m[max_i - i + min_i] = change;
    }
    for (int i = 0; i < n; i ++)
    {
        printf("%d ", m[i]);
    }
    return 0;
}   