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

int nok(int a, int b)
{
    int a_copy = a;
    int b_copy = b;
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
    return (a_copy * b_copy /((a + b)));
}

int main (void)
{
    int n, a1, a2, b1, b2, znam, chisl;
    scanf("%d", &n);
    scanf("%d", &a1);
    scanf("%d", &b1);
    znam = a1;
    chisl = b1;
    for(int i = 1; i < n; i++)
    {
        scanf("%d", &a2);
        scanf("%d", &b2);
        znam = nok(b1, b2);
        chisl = (znam / b1) * a1 + (znam / b2) * a2;
        a1 = chisl;
        b1 = znam;
    }
    int x = chisl/ znam;
    int y = chisl - znam * x;
    if (y == 0)
    {
        znam = 1;
    }
    a1 = nod(y, znam);
    y = y / a1;
    znam = znam / a1;
    printf("%d %d %d", x, y, znam);
}