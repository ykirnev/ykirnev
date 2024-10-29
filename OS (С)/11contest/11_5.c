#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
    int num = 1;
    pid_t pid_father = getpid();
    while (scanf("%d", &num) != EOF) {
        pid_t pid = fork();
        if (pid == -1) {
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                printf("%d\n", num);
                fflush(stdout);
                exit(EXIT_SUCCESS);
            } else if (getpid() == pid_father) {
                printf("-1\n");
                fflush(stdout);
                exit(EXIT_SUCCESS);
            }
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
