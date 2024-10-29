#include <stdio.h>

int main(void)
{
    unsigned int n, mask, max, tmp;
    int k;
    mask = 0;
    max = 0;
    scanf("%u", &n);
    scanf("%d", &k);
    for (int i = 0; i < k; i ++)
    {
        mask = mask | 1 << i;
    }
    for (int i = k; i <= 32; i++)
    {
        tmp = n & mask;
        if (max < tmp)
        {
            max = tmp;
        }
        n = (n >> 1);

    }
    printf("%u\n", max);
    return 0;
}