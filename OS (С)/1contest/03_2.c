#include <stdio.h>

long long int
fast_pow (long long int x, long long int degree, long long int mod)
{
    long long pow = 1;
    while (degree > 0) {
        if (degree % 2 == 0) {
            degree = degree / 2;
            x = x * x % mod;
        } else {
            degree = degree - 1;
            pow = pow * x % mod;
        } 
    }
    return pow % mod;
}

int
main(void)
{
    long long int n, answer;
    scanf("%lld", &n);
    for (int i = 1; i < n; i ++) {
        printf("0 ");
    }
    printf("\n");
    for (int a = 1; a < n; a ++) {
        for (int b = 1; b < n; b ++) {
            answer = (a * fast_pow(b , n - 2, n)) % n;
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