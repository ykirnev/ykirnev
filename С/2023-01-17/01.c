#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char* fibocci(char*s)
{
    char *answer=(char *)malloc(1001*sizeof(char));
    for (int i = 0; i < 1001; i ++)
    {
        answer[i] = '\0';
    }
    int fib1=1;
    int fib2=1;
    int sum=fib1+fib2;
    int len=0;
    while (sum - fib2 < strlen(s))
    {
        for (int i=sum-fib2;(i<sum && i<strlen(s));i++)
        {
            
            answer[len]=s[i];
            len++;
        }
        fib1=fib1+fib2;
        fib2=fib2+fib1;
        sum+=(fib1+fib2);
    }
    return answer;
}


int main(void)
{
    char *str=malloc(0*sizeof(char));
    int len=0;
    char c;
    while (((c=getchar())!=EOF)&&(c!='\n'))
    {
        len++;
        str=(char *)realloc(str, len*sizeof(char));
        str[len-1]=c;
    }
    str[len]='\0';
    printf("%s", fibocci(str));
    return 0;
}