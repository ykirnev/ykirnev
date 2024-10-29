#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    int cnt = 0;
    int status;
    for (int i = 1; i < argc; i++) {
        if ((argv[i][0] == 's') || (argv[i - 1][0] == 's')) {
            while (wait(&status) > 0) {
                if ((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) {
                    cnt += 1;
                }
            }
        }
        if (!fork()) {
            execlp(argv[i] + 1, argv[i] + 1, NULL);
            exit(1);
        }
    }
    while (wait(&status) > 0) {
        if ((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) {
            cnt += 1;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
