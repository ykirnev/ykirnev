#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

enum
{
    R_BIT_MASK = 0b100000000,
    W_BIT_MASK = 0b10000000,
    X_BIT_MASK = 0b00001000000
};

int
main(int argc, char *argv[]) {
    int input;
    const char buf[9] = "rwxrwxrwx";
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i],"%o", &input);
        if ((R_BIT_MASK & input) != 0) {
            printf("%c", buf[0]);
        }
        else {
            printf("-");
        }
        if ((W_BIT_MASK & input) != 0) {
            printf("%c", buf[1]);
        }
        else {
            printf("-");
        }
        if ((X_BIT_MASK & input) != 0) {
            printf("%c", buf[2]);
        }
        else {
            printf("-");
        }
        input = input << 3;
        if ((R_BIT_MASK & input) != 0) {
            printf("%c", buf[3]);
        }
        else {
            printf("-");
        }
        if ((W_BIT_MASK & input) != 0) {
            printf("%c", buf[4]);
        }
        else {
            printf("-");
        }
        if ((X_BIT_MASK & input) != 0) {
            printf("%c", buf[5]);
        }
        else {
            printf("-");
        }
        input = input << 3;
        if ((R_BIT_MASK & input) != 0) {
            printf("%c", buf[6]);
        }
        else {
            printf("-");
        }
        if ((W_BIT_MASK & input) != 0) {
            printf("%c", buf[7]);
        }
        else {
            printf("-");
        }
        if ((X_BIT_MASK & input) != 0) {
            printf("%c", buf[8]);
        }
        else {
            printf("-");
        }
        printf("\n");
    }
}