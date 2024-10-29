#include <stdio.h>

int main(void)
{
    int n;
    long int max_1, max_2, min_1, min_2, prmax, prmin, x;
    scanf("%d", &n);
    scanf("%ld", &max_1);
    scanf("%ld", &max_2);
    if (max_1 < max_2)
    {
        prmax = max_2;
        max_2 = max_1;
        max_1 = prmax;
    }
    min_1 = max_2;
    min_2 = max_1;
    for (int i = 2; i < n; i ++)
    {
        scanf("%ld", &x);
        if (x > max_1)
        {
            max_2 = max_1;
            max_1 = x;
        }
        else if(x > max_2)
        {
            max_2 = x;
        }
        if (x < min_1)
        {
            min_2 = min_1;
            min_1 = x;
        }
        else if(x < min_2)
        {
            min_2 = x;
        }
    }
    prmax = max_1 * max_2;
    prmin = min_1 * min_2;
    if (prmax > prmin)
    {
        printf("%ld %ld", max_2, max_1);
    }
    else
    {
        printf("%ld %ld", min_1, min_2);
    }
    return 0;
}