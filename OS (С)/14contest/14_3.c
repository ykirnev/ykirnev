#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

void *
func(const char *name)
{
    FILE *f = fopen(name, "r");
    if (f == NULL) {
        exit(EXIT_FAILURE);
    }
    char str[PATH_MAX];
    char *fgets_flag = fgets(str, sizeof(str), f);
    if (fgets_flag == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < sizeof(str); i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
    fclose(f);
    if (!fork()) {
        execlp(str, str, NULL);
        _exit(EXIT_FAILURE);
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int i = 2;
    while ((i < n + 2) && (i < argc)) {
        func(argv[i]);
        i++;
    }
    int cnt = 0;
    int status;
    while (wait(&status) != -1) {
        if ((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) {
            cnt++;
        }
    }
    while (i < argc) {
        func(argv[i]);
        i++;
        int status;
        while (wait(&status) != -1) {
            if ((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) {
                cnt++;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
