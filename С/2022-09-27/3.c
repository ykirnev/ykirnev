#include <stdio.h>

int main (void)
{
    int i, j, x;
    int s = 0;
    scanf("%d", &x);
    for (i = 0; i <= x; i ++)
    {
        for (j = 0; j <= x; j++)
        {
            s = s + i * j;
        }
    }
    printf("%d", s);
    return 0;
}   