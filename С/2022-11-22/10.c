#include <stdio.h>
#include <string.h>

int digit(char x)
{
    int y = x - '0';
    return(y);   
}

int isDigit(char c)
{
    if (('0' <= c) &&  (c <= '9'))
    {
        return 1;
    }
    return 0;
}
int isOperation(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    char s[2001];
    char c;
    for(int i = 0; i < 2001; i++)
    {
        s[i] = '\0';
    }
    int pos = 0;
    while ((c = getchar()) != '\n')
    {
        s[pos] = c;
        pos++;
    }
    for(int i = 0; i < strlen(s) - 2; i ++)
    {
        if (isDigit(s[i]) && isOperation(s[i + 1]) && isDigit(s[i + 2]))
        {
            char chislo1[2001];
            char chislo2[2001];
            for(int j = 0; j < 2001; j++)
            {
                chislo1[j] = '\0';
                chislo2[j] = '\0';
            }
            int tmp = i;
            while(tmp >= 0 && isDigit(s[tmp]))
            {
                tmp--;
            }
            pos = 0;
            for(int j = tmp + 1; j <= i; j++)
            {
                chislo1[pos] = s[j];
                pos++;
            }
            tmp = i + 2;
            while(tmp <= strlen(s) && isDigit(s[tmp]))
            {
                tmp++;
            }
            pos = 0;
            for(int j = i + 2; j < tmp; j++)
            {
                chislo2[pos] = s[j];
                pos++;
            }
            int c1 = 0;
            int c2 = 0;
            for(int j = 0; j < strlen(chislo1); j++)
            {
                c1 = c1 * 10 + digit(chislo1[j]);
            }
            for(int j = 0; j < strlen(chislo2); j++)
            {
                c2 = c2 * 10 + digit(chislo2[j]);
            }
            int answer = 0;
            int flag = 1;
            if (s[i + 1] == '+')
            {
                answer = c1 + c2;
            }
            if(s[i + 1] == '-')
            {
                answer = c1 - c2;
            }
            if(s[i + 1] == '*')
            {
                answer = c1 * c2;
            }
            if(s[i + 1] == '/')
            {
                if (c2 != 0)
                {
                    answer = c1 / c2;
                }
                else
                {
                    flag = 0;
                }
            }
            if (answer > 120000)
            {
                flag = 0;
            }
            if (answer < -120000)
            {
                flag = 0;
            }
            if (flag == 1)
            {
                printf("%d %c %d = %d\n", c1, s[i + 1], c2, answer);
            }
        }
    }
}