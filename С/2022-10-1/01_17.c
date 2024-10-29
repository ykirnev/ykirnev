#include<stdio.h>

int main(void)
{
    int n, x, new;
    scanf("%d", &n);
    scanf("%d", &x);
    for (int i = 1; i < n; i ++)
    {
        scanf("%d", &new);
        x = x ^ new;
    }
    printf("%d", x);

}