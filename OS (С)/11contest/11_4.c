#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
    int n;
    pid_t pid;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("%d", i + 1);
        fflush(stdout);
        if (i == n - 1) {
            printf("\n");
            fflush(stdout);
            return 0;
        }
        printf(" ");
        fflush(stdout);
        pid = fork();
        if (pid > 0) {
            break;
        }
    }
    wait(NULL);
    return 0;
}