#include<stdio.h>

int nod(int a, int b)
{
    while (a != 0 && b!= 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else 
        {
            b = b % a;
        }
    }
    return (a + b);
}
int main(void)
{
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("%d", nod(nod (a, b), nod(c, d)));
    return 0;
}