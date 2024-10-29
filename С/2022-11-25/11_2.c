#include <stdio.h>
#include <stdlib.h>


int mx(int x1, int x2)
{
    if (x1 > x2)
    {
        return x1;
    }
    return x2;
}

int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);
    n = n + 2;
    m = m + 2;
    int Mas[n][m];
    int Mas_max[n][m];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            Mas[i][j] = 0;
            Mas_max[i][j] = 0;
        }
    }
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            scanf("%d", &Mas[i][j]); 
            Mas_max[i][j] = Mas[i][j];
        }
    }

    for (int j = 2; j < m - 1; j++)
    {
        for (int i = 1; i < n - 1; i++)
        {
            Mas_max[i][j] = Mas[i][j] + mx(Mas_max[i - 1][j - 1], mx(Mas_max[i][j - 1], Mas_max[i + 1][j - 1]));
        }
    }
    int max = Mas_max[1][m - 2];
    for(int i = 1; i < n-1; i++)
    {
        if (Mas_max[i][m - 2] > max)
        {
            max = Mas_max[i][m - 2];
        }
    }
    printf("%d", max);
    
}