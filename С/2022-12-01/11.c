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
    char o;
};


long long int chislo (char c)
{
    long long int a;
    a = c - '0';
    return a;
}





int main(void)
{
    FILE *output, *input;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int flag_chisla = 0;
    long long int tmp = 0;
    long long int digit;
    struct stack_operations* operation;
    struct stack_numbers * chisla;
    operation = (struct stack_operations*)malloc(sizeof(struct stack_operations));
    chisla = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
    char x = '1';
    do
    {
        x = fgetc(input);
        if ((x >= '0') && (x <= '9'))
        {
            digit = chislo(x);
            tmp = tmp * 10 + digit;
            if (flag_chisla == 0)
            {
                flag_chisla = 1;
            }
        }
        else if (x == '+'|| x == '-' || x == '*' || x == '/' || x == ')' || x == '(')
        {
            if (flag_chisla == 1)
            {
                flag_chisla = 0;
                chisla -> x = tmp;
                chisla -> up = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                chisla -> up -> down = chisla;
                chisla = chisla -> up;
                chisla -> up = NULL;
                tmp = 0;
            }
            tmp = 0;
            while(1)
            {
                if (x == '+' || x == '-')
                {
                    if ((operation -> o) == '+' || (operation -> o) == '-' || (operation -> o) == '*' || (operation -> o) == '/')
                    {
                        if ((operation -> o) == '+' ) tmp = chisla -> down -> x + chisla -> down -> down -> x;
                        if ((operation -> o) == '-' ) tmp = chisla -> down -> down -> x - chisla -> down -> x;
                        if ((operation -> o) == '*' ) tmp = chisla -> down -> x * chisla -> down -> down -> x;
                        if ((operation -> o) == '/' ) tmp = chisla -> down -> down -> x / chisla -> down -> x;
                        printf("%lld", tmp);
                        chisla -> down = chisla -> down -> down -> down;
                        free(chisla -> down -> up -> up);
                        free(chisla -> down -> up);
                        chisla -> down -> up = chisla;
                        chisla -> x = tmp;
                        chisla -> up = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                        chisla -> up -> down = chisla;
                        chisla = chisla -> up;
                        chisla -> up = NULL;
                        operation -> down = operation -> down -> down;
                        free(operation -> down -> up);
                        operation -> down -> up = operation;
                    }
                    else
                    {
                        operation -> o = x;
                        operation -> up = (struct stack_operations*)malloc(sizeof(struct stack_operations));
                        operation -> up -> down = operation;
                        operation = operation -> up;
                        operation -> up = NULL;
                        break;
                    }
                }
                if (x == '(')
                {
                    operation -> o = x;
                    operation -> up = (struct stack_operations*)malloc(sizeof(struct stack_operations));
                    operation -> up -> down = operation;
                    operation = operation -> up;
                    operation -> up = NULL;
                    break;
                }
                if (x == ')')
                {
                    operation -> down = operation -> down -> down;
                    free(operation -> down -> up);
                    operation -> down -> up = operation;
                    break;
                }
                if (x == '*' || x == '/')
                {
                    if ((operation -> o) == '*' || (operation -> o) == '/')
                    {
                        if ((operation -> o) == '*') tmp = chisla -> down -> x * chisla -> down -> down -> x;
                        if ((operation -> o) == '/') tmp = chisla -> down -> x / chisla -> down -> down -> x;
                        chisla -> down = chisla -> down -> down -> down;
                        free(chisla -> down -> up -> up);
                        free(chisla -> down -> up);
                        chisla -> down -> up = chisla;
                        chisla -> x = tmp;
                        chisla -> up = (struct stack_numbers*)malloc(sizeof(struct stack_numbers));
                        chisla -> up -> down = chisla;
                        chisla = chisla -> up;
                        chisla -> up = NULL;
                        operation -> down = operation -> down -> down;
                        free(operation -> down -> up);
                        operation -> down -> up = operation;
                    }
                    else
                    {
                        operation -> o = x;
                        operation -> up = (struct stack_operations*)malloc(sizeof(struct stack_operations));
                        operation -> up -> down = operation;
                        operation = operation -> up;
                        operation -> up = NULL;
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }while (x != EOF);
    printf("%d", chisla->down -> x);
    fprintf(output, "%d", chisla->down -> x);
}