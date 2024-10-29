#include <stdio.h>
#include <stdlib.h>
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
    int n;
    scanf("%d", &n);
    int **Mas;
    n = n + 4;
    Mas = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        Mas[i] = (int*)malloc(n* sizeof(int));
        for (int j = 0; j < n; j++)
        {
            Mas[i][j] = 0;
        }
    }
    int x1, x2, y1, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    x1 = x1 + 1;
    y1 = y1 + 1;
    x2 = x2 + 1;
    y2 = y2 + 1;
    Mas[x1][y1] = 1;
    int flag = 0;
    if ((x1 == x2) && (y1 == y2))
    {
        printf("0");
        flag = 1;
    }
    int counter = 2;
    while ((counter < 3 * n) && (flag != 1))
    {
        for (int i = 2; i < n - 2; i++)
        {
            for (int j = 2; j < n - 2;  j++)
            {
                if ((Mas[i + 1][j + 2] == counter - 1) || (Mas[i + 2][j + 1] == counter - 1) || (Mas[i + 2][j - 1] == counter - 1) || (Mas[i + 1][j - 2] == counter - 1) || (Mas[i - 1][j - 2] == counter - 1) || (Mas[i - 2][j - 1] == counter - 1) || (Mas[i - 2][j + 1] == counter - 1) || (Mas[i - 1][j + 2] == counter - 1))
                {
                    if (Mas[i][j] == 0)
                    {
                        Mas[i][j] = counter;
                        if ((i == x2) && (j == y2))
                        {
                        printf("%d", counter - 1);
                        flag = 1;
                        break;
                        }
                    }
                }
            }
        }
        counter++;
    }
    if (flag == 0)
    {
        printf("-1");
    }
}