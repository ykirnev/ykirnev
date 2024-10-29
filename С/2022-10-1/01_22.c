#include<stdio.h>
int modul(int x)
{
    if (x < 0)
    {
        return x * (-1);
    }
    return x;
}
int mn(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}
int main(void)
{
    int x, y, razn;
    scanf("%d %d", &x, &y);
    razn = modul(modul(x) - modul(y));
    razn = razn * 2 - razn % 2;
    printf("%d", mn(modul(x), modul(y)) * 2 + razn);
}