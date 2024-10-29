#include <stdio.h>

int main(void)
{
    unsigned int n, mask = 1, c = 0;
    scanf("%u", &n);
    while (n > 0)
    {
        c = c + (mask & n);
        n = n >> 1;
    }
    printf("%d", c);
    return 0;
}