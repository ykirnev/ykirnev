#include <stdlib.h>
#include<stdio.h>

void prn(int **Mas, int n, int m)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", Mas[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);
    int number;
    n = n + 2;
    m = m + 2;
    scanf("%d", &number);
    int **Mas_tmp;
    Mas_tmp = (int **) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++)
    {
        Mas_tmp[i] = (int*) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            Mas_tmp[i][j] = 0;
        }
    }
    int sm = 0;
    for (int i = 0; i < number; i ++)
    {
        int x, y;
        scanf ("%d %d", &x, &y);
        if (Mas_tmp[x][y] != 1)
        {
            sm++;
        }
        Mas_tmp[x][y] = 1;
    }
    int counter = 2;
    int cnt0 = (n - 2) * (m - 2) - sm;
    while (cnt0 > 0)
    {
        for (int i = 1; i < m - 1; i ++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if ((Mas_tmp[i + 1][j] == (counter - 1)) || (Mas_tmp[i][j + 1] == (counter - 1)) ||(Mas_tmp[i - 1][j] == (counter - 1)) || (Mas_tmp[i][j - 1] == (counter - 1)))
                {
                    if (Mas_tmp[i][j] == 0)
                    {
                        cnt0 = cnt0 - 1;
                        Mas_tmp[i][j] = counter;
                    }
                }
            }
        }
        counter ++;
    }
    printf("%d", counter - 2);
}