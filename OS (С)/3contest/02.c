#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv)
{
    long long int sum_pos = 0;
    long long int sum_neg = 0;
    int a;
    int x;
    for (int i = 1; i < argc; i++) {
        a = sscanf(argv[i], "%d", &x);
        if (a == 0)
        {
            return 0;
        }
        if (x > 0) {
            sum_pos = sum_pos + x;
        }
        else {
            sum_neg = sum_neg + x;
        }
    }
    printf("%lld\n", sum_pos);
    printf("%lld\n", sum_neg);
}