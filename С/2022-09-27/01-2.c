#include <stdio.h>

int main (void)
{
    int n, x, max, counter;
    scanf("%d", &n);
    scanf("%d", &x);
    max = x;
    counter = 1;
    for (int i = 0; i < (n - 1); i ++)
    {
        scanf("%d", &x);
        if (max == x)
        {
            counter ++;
        }
        else if (max < x)
        {
            max = x;
            counter = 1;
        }
    }
    printf("%d", counter);


    return 0;
}   