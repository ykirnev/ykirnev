#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(int argc, char **argv)
{
    double rate = 0;
    double change;
    if (argc == 1) {
        return 0;
    }
    sscanf(argv[1], "%lf", &rate);
    rate = rate * 1e+4;
    for (int i = 2; i < argc; i++) {
        sscanf(argv[i], "%lf", &change);
        change = (100.0 + change) / 100.0;
        rate = rate * change;
        rate = round(rate);
    }
    rate = rate / 1e+4;
    printf("%.4lf\n", rate);
    return 0;
}