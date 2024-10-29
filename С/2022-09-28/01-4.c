#include <stdio.h>

int main(void)
{
    int n, x1, x2;
    scanf("%d", &n);
    scanf("%d", &x1);
    int max_counter = 0;
    int tmp_counter = 1;
    for (int i = 0; i < n - 1; i ++)
    {
        scanf("%d", &x2);
        if (x2 > x1)
        {
            tmp_counter ++;
        }
        else{
            if (tmp_counter > max_counter)
            {
                max_counter = tmp_counter;
            
            }
            tmp_counter = 1;
        }
        x1 = x2;
    }
    if (tmp_counter > max_counter)
        {
            max_counter = tmp_counter;
        }
    if (n == 1)
    {
        printf("1");
    }
    else 
    {
        printf("%d", max_counter);
    }
    return 0;
}