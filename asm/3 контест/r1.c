#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x, i;
    scanf("%d", &i);
    int b = 1;
    x = 0;
    for(int j = 0; j < i; j++)
    {
        x ^= b;
        b ^= x;
        x ^= b;
        b += x;
    }
    printf("%d\n", x);
    return 0;
}