#include <stdio.h>

int main(void)
{
    unsigned int n;
    unsigned short a, b, c, d;
    n = 0;
    scanf("%hu %hu %hu %hu", &a, &b, &c, &d);
    n = (d << 24) | (c << 16) | (b << 8) | (a);
    printf("%u", n);
    return 0;
}