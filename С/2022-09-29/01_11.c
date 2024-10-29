#include <stdio.h>

int main (void)
{
    unsigned int n, mask;
    mask = 0;
    for (int i = 24; i < 32; i ++)
    {
        mask = mask | (1 << i);
    }

    scanf("%u", &n);
    printf("%u", n ^ mask);
    return 0;
}   