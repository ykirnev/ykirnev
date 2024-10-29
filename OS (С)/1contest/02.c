#include <stdio.h>
enum
{
    MASK_2 = 0b11111011,
    MASK_3 = 0b00001000
};
int
main(void)
{
    int c;
    while ((c = getchar()) != EOF) {
        if ((c <= '9') && (c >= '0')) {
            c = c - '0' + 1;
        } else if ((c <= 'z') && (c >= 'a')) {
            c = c - 'a' + 11;
        } else if ((c <= 'Z') && (c >= 'A')) {
            c = c - 'A' + 37;
        } else {
            continue;
        }
        c = c & MASK_2;
        c = c ^ MASK_3;
        if (c == 0) {
            printf("@");
        } else if (c == 63) {
            printf("#");
        } else if ((c <= 10) && (c >= 1)) {
            c = c + '0' - 1;
            printf("%c", c);
        } else if ((c <= 37) && (c >= 11)) {
            c = c + 'a' - 11;
            printf("%c", c);
        } else {
            c = c + 'A' - 37;
            printf("%c", c);
        }
    }
    return 0;
}
