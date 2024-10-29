#include<stdio.h>
int a[14];
void prn(int k)
{
    for (int i = 0; i < k; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int check(int k)
{
    int flag = 0;
    for(int i = 0; i < k; i++)
    {
        for(int j = i + 1; j < k; j++)
        {
            if (a[j] == a[i])
            {
                flag = 1;
            }
        }
    }
    for(int i = 1; i < k; i++)
    {
        if (a[i - 1] >= a[i])
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        return 0;
    }
    return 1;
}
int step(int n, int k, int key)
{
    int i;
    if (a[k - 1] < n-1)
    {
        a[k-1]++;
    }
    else {
        for(i = k - 2; i >= 0; i--)
            if ((a[i + 1] - a[i] > 1)){
                break;
            }
        if (i == -1)
        {
            return 0;
        }
        a[i]++;
        for(i = i + 1; i<k; i++) 
        {
            a[i] = a[i-1] + 1;
        }
    }
    return 1;
}

int main(void)
{
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        a[i] = i;
    }
    int key = 1;
    while (key == 1)
    {
        if (check (k) == 1)
        {
            prn(k);
        }
        key = step(n, k, key);
    }
    return 0;
}