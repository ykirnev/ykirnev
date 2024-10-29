#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[2000001];
    int cnt = 0;
    char c;
    for(int i = 0; i < 2000001; i++)
    {
        s[i] = '\0';
    }
    int pos = 0;
    while ((c = getchar()) != '\n')
    {
        s[pos] = c;
        pos++;
        if (c == '0')
        {
            cnt++;
        }
    }
    int Mas[cnt];
    pos = 0;
    for(int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '0')
        {
            Mas[pos] = i;
            pos++;
        }
    }
    int min_Mas[cnt];
    int min = 0;
    for (int i = 0; i <= cnt; i++)
    {
        min_Mas[i] = Mas[i];
    }
    int new_Mas[cnt];
    for(int i = 0; i < cnt; i++)
    {
        pos = 0;
        for (int j = i; j < cnt; j++)
        {
            new_Mas[pos] = Mas[j] - Mas[i];
            pos++;
        }
        for (int j = 0; j < i; j++)
        {
            new_Mas[pos] = (strlen(s) + strlen(s) + Mas[j] - Mas[i]) % strlen(s);
            pos++;
        }
        for (int j = 0; j < cnt; j++)
        {
            if (min_Mas[j] < new_Mas[j])
            {
                break;
            }
            if (min_Mas[j] > new_Mas[j])
            {
                for (int k = 0; k < cnt; k++)
                {
                    min_Mas[k] = new_Mas[k];
                    min = Mas[i]; 
                }
            }
        }
    }

    for (int j = 0; j < cnt; j++)
    {
        if (min_Mas[j] < new_Mas[j])
        {
            break;
        }
        if (min_Mas[j] > new_Mas[j])
        {
            for (int k = 0; k < cnt; k++)
            {
                min_Mas[k] = new_Mas[k];
                min = Mas[cnt - 1]; 
            }
        }
        }
    char answer[2000001];
    for (int i = 0; i < 2000001; i++)
    {
        answer[i] = '\0';
    }
    
    cnt = 0;
    for (int i = min; i < strlen(s); i++)
    {
        answer[cnt] = s[i];
        cnt++;
    }
    for (int i = 0; i < min; i++)
    {
        answer[cnt] = s[i];
        cnt++;
    }
    printf("%s", answer);
}