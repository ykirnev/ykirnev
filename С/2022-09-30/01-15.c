#include <stdio.h>

int main (void)
{
    int n, x1, x2, y1, y2, y3, x3, flag = 0, x_first, y_first, x_second, y_second;

    scanf("%d", &n);
    scanf("%d", &x1);
    scanf("%d", &y1);
    scanf("%d", &x2);
    scanf("%d", &y2);
    x_first = x1;
    y_first = y1;
    x_second = x2;
    y_second = y2;
    for (int i = 2; i < n; i ++)
    {
        scanf("%d", &x3);
        scanf("%d", &y3);

        if ((((x2 - x1) * (y2- y3)) - ((y2 - y1) * (x2 - x3))) < 0)
        {
            flag = flag + 1;   
        }
        x1 = x2;
        y1 = y2;
        y2 = y3;
        x2 = x3;
    }
    if ((((x_first - x3) * (y_first- y_second)) - ((y_first - y3) * (x_first - x_second))) < 0)
    {
        flag = flag + 1;   
    }
    if ((((x2 - x1) * (y2- y_first)) - ((y2 - y1) * (x2 - x_first))) < 0)
        {
            flag = flag + 1;   
        }
    if (flag == 0 || flag == n)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}