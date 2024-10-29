#include <stdio.h>
#include <stdlib.h>

int* sdvig(int* Mas, int n, int par)
{
    int* answer;
    answer = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (Mas[i] == par)
        {
            par = i;
            break;
        }
    }
    int pos = 0;
    for(int i = par; i < n; i++)
    {
        answer[pos] = Mas[i]; 
        pos++;
    }
    for(int i = 0; i < par; i++)
    {
        answer[pos] = Mas[i]; 
        pos++;
    }
    free(Mas);
    return answer;
}

int main(void)
{
    FILE *output, *input;
    int n, m;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    fscanf(input, "%d %d", &n, &m);
    int* Mas;
    int par;
    Mas = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        Mas[i] = i + 1;
    }
    for(int i = 0; i < m; i++)
    {
        fscanf(input, "%d", &par);
        Mas = sdvig(Mas, n, par);
    }   

    for(int i = 0; i < n; i++)
    {
        fprintf(output, "%d ", Mas[i]);
    }


}