#include <stdio.h>

long long int
fast_pow (long long int x, long long int p, long long int mod)
{
    
}

int
main(void)
{
    long long int n, answer;

    for (int n = 0; n < 2000; n++){
        printf("%lld\n", n);
        for (int i = 1; i < n; i ++) {
            //printf("0 ");
        }
        //printf("\n");
        for (long long int a = 1; a < n; a ++) {
            for (long long int b = 1; b < n; b ++) {
                answer = (a * fast_pow(b , n - 2, n)) % n;
                if (answer < 0)
                {
                    answer = n + answer;
                }
                //printf("%lld ", answer);
            }
            //printf("\n");
        }
    }
    return 0;
}