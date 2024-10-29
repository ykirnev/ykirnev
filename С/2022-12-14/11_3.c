#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int Mas[100001];
char Op[100001];

long long int digit (char c)
{
    long long int a;
    a = c - '0';
    return a;
}

long long int func(char * line, int len_line)
{
    int i = 0;
    int Mas_i = 0;
    int Op_i = 0;
    int tmp = 0;
    int new_digit = 0;
    char c;
    while(i != len_line)
    {
        c = line[i];
        if (c <= '9' && c >= '0')
        {
            tmp = tmp * 10 + digit(c);
            new_digit = 1;
        }
        else
        {
            if (new_digit != 0)
            {
            Mas[Mas_i] = tmp;
            Mas_i++;
            new_digit = 0;
            }
            if (c == '+' || c == '-')
            {
                while (Op_i!= 0 && Op[Op_i - 1] != '(' && Mas_i - 1!= 0)
                {
                    if (Op[Op_i - 1] == '+') Mas[Mas_i - 2] += Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '-') Mas[Mas_i - 2] -= Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '*') Mas[Mas_i - 2] *= Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '/') Mas[Mas_i - 2] /= Mas[Mas_i - 1];
                    Op_i -= 1;
                    Mas_i -= 1;
                }
                Op_i++;
                Op[Op_i - 1] = c;
            }
            else if (c == '*' || c == '/')
            {
                while (Op_i != 0 && Op[Op_i - 1] != '(' && Mas_i -1 != 0 && Op[Op_i - 1] != '+' && Op[Op_i - 1] != '-')
                {
                    if (Op[Op_i - 1] == '*') Mas[Mas_i - 2] *= Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '/') Mas[Mas_i - 2] /= Mas[Mas_i - 1];
                    Op_i -= 1;
                    Mas_i -= 1;
                }
                Op_i++;
                Op[Op_i - 1] = c;
            }
            else if (c == '(')
            {
                Op_i++;
                Op[Op_i - 1] = '(';
            }
            else{
                while (Op_i != 0 && Op[Op_i - 1] != '(' && Mas_i != 0)
                {
                    if (Op[Op_i - 1] == '+') Mas[Mas_i - 2] += Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '-') Mas[Mas_i - 2] -= Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '*') Mas[Mas_i - 2] *= Mas[Mas_i - 1];
                    if (Op[Op_i - 1] == '/') Mas[Mas_i - 2] /= Mas[Mas_i - 1];
                    Op_i -= 1;
                    Mas_i -= 1;
                }
                Op_i -= 1;
            }
            tmp = 0;
        }
        i++;
    }
    if (Mas_i - 1!= 0)
    {
        if (Op[Op_i] == '+') Mas[Mas_i - 2] += Mas[Mas_i - 1];
        if (Op[Op_i] == '-') Mas[Mas_i - 2] -= Mas[Mas_i - 1];
        if (Op[Op_i] == '*') Mas[Mas_i - 2] *= Mas[Mas_i - 1];
        if (Op[Op_i] == '/') Mas[Mas_i - 2] /= Mas[Mas_i - 1];
        Op_i -= 1;
        Mas_i -= 1;
    }
    return Mas[Mas_i - 1];
}


int main(void)
{
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    char *line;
    int len_line = 100000 * 11 + 1;
    line = (char *)malloc(len_line * sizeof(char));
    char c;
    int i;
    for (i = 0; i < len_line; i++)
    {
        line[i] = '\0';
    }
    int pos = 0;
    fscanf(input, "%c", &c);
    while (c != EOF)
    {
        if ((c != ' ') && (c != '\n')){
            line[pos] = c;
            pos++;
        }
        c = fgetc(input);
    }
    len_line = pos + 1;
    for (i = 0; i < 100000; i++)
    {
        Mas[i] = 0;
        Op[i] = ' ';
    }
    i = 0;
    long long int answer = func(line, len_line);
    fprintf(output, "%lld", answer);
    free(line);
}
