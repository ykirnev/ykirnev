#include <stdio.h>
int main(void)
{
    int n, x, counter = 0;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        a[i] = x;
    }
    for(int i = 1; i <= n - 2; i ++)
    {
        for(int j = i + 2; j <= n; j ++)
        {
            int k = (i + j)/2;
            if ((a[k - 1] == (a[i - 1] + a[j - 1])/2) && (i < k) && (k < j) && ((i + j) % 2 == 0) && ((a[j - 1] + a[i - 1])% 2 == 0))
            {
                counter ++;
            }
        }
    }
    printf("%d", counter);
}