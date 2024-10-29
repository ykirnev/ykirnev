#include <stdio.h>

int main (void)
{
    int min = 100000000;
    int max = 0;
    int x, n;
    int flag = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        if (x < min){
            min = x;
            flag = flag + 1;
        }
        if (x > max)
        {
            max =x;
            flag = flag + 1;
        }
    }
    if (flag >= 2)
    {
       printf("%d", max - min); 
    }
    else{
        printf("0");
    }
    return 0;
}   
