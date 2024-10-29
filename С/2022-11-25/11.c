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
    int n , m;
    scanf("%d %d", &n, &m);
    n = n + 2;
    m = m + 2;
    int Mas[n][m];
    int Mas_max[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Mas[i][j] = 0;
            Mas_max[i][j] = 0;
        }
    }
    int max = 0;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            scanf("%d", &Mas[i][j]);
        }
    }
    prn(Mas, n, m);

    for (int i = 0; i < n; i++)
    {
        Mas_max[i][0] = max;
    }
    prn(Mas, n, m);
    for (int i = 2; i < m - 1; i++)
    {
        for(int j = 1; j < n - 1; j++)
        {
            Mas_max[j][i] = mx(Mas_max[j - 1][i], mx(Mas_max[j][i], Mas_max[j + 1][i])) + Mas[j][i];
        }
    }
    for (int i = 1; i < m; i++)
    {
        max = mx(Mas[i][n - 1], max);
    }
    printf("%d", max);


}