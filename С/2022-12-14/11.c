#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_numbers
{
    struct stack_numbers * up;
    struct stack_numbers * down;
    long long int x;
};

struct stack_operations
{
    struct stack_operations * up;
    struct stack_operations * down;
    char op;
};


long long int digit (char c)
{
    long long int a;
    a = c - '0';
    return a;
}

void prn_Op(struct stack_operations * Op)
{
    while (Op -> down != NULL)
    {
        Op = Op -> down;
        fprintf(stderr, "%c", Op -> op);
    }
}

void prn_N(struct stack_numbers * N)
{
    while (N -> down != NULL)
    {
        N = N -> down;
        printf("%lld", N -> x);
    }
}

void func(struct stack_numbers *N, struct stack_operations *Op, char c)
{
    prn_N(N);
    printf("\n");
    int flag = 1;
    char prev;
    long long chislo;
    if (c == '+' || c == '-')
    {
        if ((Op -> down != NULL) && (N -> down -> down != NULL))
        {
            prev = Op -> down -> op;
            if (prev == '+' || prev == '*' || prev == '-' || prev == '/')
            {
                struct stack_numbers *first, *second, *new;
                first = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                second = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                first = N -> down;
                second = N -> down -> down;
                if (prev == '+')chislo = first -> x + second -> x;
                if (prev == '*')chislo = first -> x * second -> x;
                if (prev == '-')chislo = second -> x - first -> x;
                if (prev == '/')chislo = second -> x / first -> x;
                N -> down = second -> down;
                if (N -> down != NULL)
                {
                    N -> down -> up = N;
                }
                new = (struct stack_numbers *)malloc(sizeof(struct stack_numbers));
                new -> up = NULL;
                new -> down = N;
                N -> up = new;
                N -> x = chislo; 
                chislo = 0;
                N = new;
                free(first);
                free(second);
                func (N, Op -> down, Op -> down -> op);
            }
            else
            {
                flag = 0;
            }
        }
        else{
            flag = 0;
        }
    }
    if (c == '*' || c == '/')
    {
        if ((Op -> down != NULL) && (N -> down -> down != NULL))
        {
            prev = Op -> down -> op;
            if (prev == '*' || prev == '/')
            {
                struct stack_numbers *first, *second, *new;
                first = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                second = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                first = N -> down;
                second = N -> down -> down;
                if (prev == '/')chislo = second -> x / first -> x;
                if (prev == '*')chislo = first -> x * second -> x;
                N -> down = second -> down;
                if (N -> down != NULL)
                {
                    N -> down -> up = N;
                }
                new = (struct stack_numbers *)malloc(sizeof(struct stack_numbers));
                new -> up = NULL;
                new -> down = N;
                N -> up = new;
                N -> x = chislo; 
                chislo = 0;
                N = new;
                free(first);
                free(second);
                func (N, Op -> down, Op -> down -> op);
            }
            else
            {
                flag = 0;
            }
        }
        else{
            flag = 0;
        }
    }
    if (c == '(')
    {
        flag = 0;
    }
    if (c == ')')
    {
        Op = Op -> down;
        Op -> up = NULL;
        Op -> op = ' ';
    }
    if (flag == 0)
    {
        struct stack_operations* new;
        new = (struct stack_operations*)malloc(sizeof(struct stack_operations));
        new -> up = NULL;
        new -> down = Op;
        Op -> up = new;
        Op -> op = c;
        Op = new;
        fprintf(stderr, "new %c\n", c);
    }
}

int main(void)
{
    fprintf(stderr, "a\n");
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    char *line;
    int len_line = 100000 * 11 + 1;
    line = (char *)malloc(len_line * sizeof(char));
    char c;
    for (int i = 0; i < len_line; i++)
    {
        line[i] = '\0';
    }
    int pos = 0;
    int flag = fscanf(input, "%c", &c);
    while (c != EOF)
    {
        if (c != ' '){
            line[pos] = c;
            pos++;
        }
        c = fgetc(input);
    }
    pos++;
    line[pos] = '+';
    pos++;
    line[pos] = '0';
    len_line = pos;
    int flag_chisla = 0;
    long long int chislo = 0;
    struct stack_numbers *N, *new;
    N = (struct stack_numbers *)malloc(sizeof(struct stack_numbers));
    N -> up = NULL;
    N -> down = NULL;
    struct stack_operations *Op;
    Op = (struct stack_operations*)malloc(sizeof(struct stack_operations));
    Op -> up = NULL;
    Op -> down = NULL;
    for(int i = 0; i < len_line; i++)
    {
        c = line[i];
        if (c <= '9' && c >= '0')
        {
            if (flag_chisla == 0)
            {
                chislo = digit(c);
                flag_chisla = 1;
            }
            else{
                chislo = chislo * 10 + digit(c);
            }
        }
        else
        {
            if (flag_chisla == 1)
            {
                flag_chisla = 0;
                new = (struct stack_numbers *)malloc(sizeof(struct stack_numbers));
                new -> up = NULL;
                new -> down = N;
                N -> up = new;
                N -> x = chislo;
                chislo = 0;
                N = new;
            }
            func(N, Op, c);
            N = N -> down;
        }
    }
    fprintf(stderr, "b\n");
    N = N -> down;
    fprintf(output, "%lld", N -> x);
}