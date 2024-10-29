#include <stdio.h>
#include <stdlib.h>

int main()
{
    double x, y;
    scanf("%lf", &x);
    scanf("%lf", &y);
    if ((x >= 2.0) && (x <= 5.0)){
        if ((y >= 1.0) && (y <= 7.0)){
            if (x <= (y + 2.0)){
                printf("1");
                return 0;
            }
        }
    }
    printf("0");
    return 0;
}