#include <stdio.h>

int main(void)
{
    unsigned int n, mask;
    int k;
    mask = 0;
    scanf("%u", &n);
    scanf("%d", &k);
    for (int i = 0; i < k; i ++)
    {
        mask = mask | 1 << i;
    }
    n = n & mask;
    printf("%u\n", n);
    return 0;
}