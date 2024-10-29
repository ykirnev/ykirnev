#include <stdio.h>

int
main(void)
{
    long long int n, answer, pow;
    scanf("%lld", &n);
    for (int i = 1; i < n; i ++) {
        printf("0 ");
    }
    printf("\n");
    for (long long int a = 1; a < n; a++) {
        for (long long int b = 1; b < n; b++) {
            pow = 1;
            for (int i = 0; i < n - 2; i++) {
                pow = pow * b % n; 
            }
            answer = a * pow % n;
            if (answer < 0)
            {
                answer = n + answer;
            }
            printf("%lld ", answer);
        }
        printf("\n");
    }
    return 0;
}