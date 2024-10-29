#include<stdio.h>

int isprime(unsigned int x)
{
    int i = 1;
    if (x == 2)
    {
        return 1;
    }
    if (x == 1)
    {
        return 0;
    }
    while (i * i <= x)
    {
        i ++;
        if (x % i == 0)
        {
            return 0;
        }  
    }
    return 1;
}
int main(void)
{
    unsigned int n;
    scanf("%u", &n);
    while (isprime(n) != 1)
    {
        n ++;
    }
    printf("%u", n);
}