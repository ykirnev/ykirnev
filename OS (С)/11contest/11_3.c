#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

enum
{
    xS_OF_SONS = 3,
    SIZEOF_INPUT = 8,
    BASE = 10
};

int
main(void)
{
    char buf[SIZEOF_INPUT];
    char *end;
    int answer;
    int cnt_read;
    for (int i = 0; i < NUMBERS_OF_SONS; i++) {
        if (!fork()) {
            cnt_read = read(0, buf, sizeof(buf));
            buf[cnt_read] = '\0';
            int a = strtol(buf, &end, BASE);
            if (a == end) {
                return -1;
            }
            answer = a * a;
            printf("%d %d\n", i + 1, answer);
            fflush(stdout);
            return 0;
        }
    }
    for (int i = 0; i < NUMBERS_OF_SONS; i++) {
        wait(NULL);
    }
    return 0;
}
