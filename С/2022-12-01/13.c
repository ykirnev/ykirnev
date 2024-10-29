#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
    FILE *output, *input;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int n, i, pos, cnt, number;
    fscanf(input, "%d", &n);
    char *line;
    char x;
    char *tmp_cmp;
    char *flag;
    char *Mas_line[10000];
    char *Mas_cmp[10000];
    number = 0;
    line = malloc(sizeof(2001 * sizeof(char)));
    flag = fgets(line, 2001, input);
    while(1)
    {
        line = malloc(sizeof(2001 * sizeof(char)));
        tmp_cmp = malloc(sizeof(101 * sizeof(char)));
        for(int i = 0; i < 101; i++)
        {
            tmp_cmp[i] = '\0';
        }
        for (int i = 0; i < 2001; i++)
        {
            line[i] = '\0';
        }
        pos = 0;
        while (1){
            fscanf(input, "%c", x);
            if (x == '\n' || x == '\0')
            {
                break;
            }
            line[pos] = x;
            pos++;
        }
        cnt = 0;
        pos = 0;
        for(i = 0; i < strlen(line); i++)
        {
            if (line[i] == ';')
            {
                cnt++;
                if (cnt == n)
                {
                    pos = i;
                    break;
                }  
            }
        }
        pos++;
        i = 0;
        while ((line[pos] != ';') && (line[pos] != '\n') && (line[pos] != '\0'))
        {
            tmp_cmp[i] = line[pos];
            printf("%c",line[pos]);
            pos++;
            i++; 
        }
        printf("\n");
        Mas_line[number] = line;
        Mas_cmp[number] = &line[pos];
        number++;
    }
    for(i = 0; i < number; i++)
    {
        for(int j = 0; j < strlen(Mas_line[i]); j++)
        {
            if (Mas_line[i][j]!= ' ') printf("%c", Mas_line[i][j]);
        }
        printf("____\n");
    }
    for(i = 0; i < number - 1; i++)
    {
        for (int j = 0; j < number - 1; j++)
        {
            if (strcmp(Mas_cmp[j], Mas_cmp[j + 1]) > 0)
            {
                char*swap_cmp;
                char*swap_line;
                swap_line = malloc(sizeof(2001 * sizeof(char)));
                swap_cmp = malloc(sizeof(101 * sizeof(char)));
                for(int i = 0; i < 101; i++)
                {
                    swap_cmp[i] = '\0';
                }
                for (int i = 0; i < 2001; i++)
                {
                    swap_line[i] = '\0';
                }
                for(int k = 0; k < 101; k++)
                {
                    swap_cmp[k] = Mas_cmp[j][k];
                    Mas_cmp[j][k] = Mas_cmp[j + 1][k];
                    Mas_cmp[j + 1][k] = Mas_cmp[j][k];
                }
                for(int k = 0; k < 2001; k++)
                {
                    swap_line[k] = Mas_line[j][k];
                    Mas_line[j][k] = Mas_line[j + 1][k];
                    Mas_line[j + 1][k] = Mas_line[j][k];
                }
                free(swap_cmp);
                free(swap_line);
            }
        }
    }
    for(i = 0; i < number; i++)
    {
        for(int j = 0; j < strlen(Mas_line[i]); j++)
        {
            if (Mas_line[i][j]!= ' ') printf("%c", Mas_line[i][j]);
        }
    }
    fclose(input);
    fclose(output);
}