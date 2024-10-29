#include <stdio.h>

int main (void)
{
    int answer;
    int a = 0xCA, b = 0xFE, c = 0xBA, d = 0xBE;
    unsigned int x = 0;
    x = (a << 24) | (b << 16) | (c << 8) | (d);
    printf("%x", x);
    return 0;
}   


