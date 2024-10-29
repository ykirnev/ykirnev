#include <stdlib.h>
#include <stdio.h>
//Кирнев Юра 105 группа

int comp(const void *x, const void *y)
{
    if (*(int*)x < *(int*)y) return *(int*)x;
    if (*(int*)x == *(int*)y) return 0;
    return *(int*)y;
}

int main(void)
{
    FILE *in, *out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int Mas[1000];
    int cnt = 0;
    int x;
    while(fscanf(in, "%u", &x) == 1)
    {
        Mas[cnt] = x;
        cnt = cnt + 1;
    }
    qsort(Mas, cnt, 4, comp);
    for (int i = 0; i < cnt; i ++)
    {
        fprintf(out, "%u ", Mas[i]);
    }
    return 0;
}