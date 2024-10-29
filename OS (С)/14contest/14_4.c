#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int fd[2];
int max_value;

void
handl(int sig)
{
    FILE *file_in = fdopen(fd[0], "r");
    FILE *file_out = fdopen(fd[1], "w");
    fflush(stdout);
    int pid1, pid2, x;
    fscanf(file_in, "%d%d", &pid2, &x);
    if (x > max_value) {
        pid1 = getpid();
        fprintf(file_out, "%d %d\n", pid1, x);
        fflush(file_out);
        kill(pid2, SIGUSR1);
        _exit(EXIT_SUCCESS);
    } else if (x % 2 == 0) {
        fprintf(stdout, "2 %d\n", x);
        fflush(stdout);
    } else {
        fprintf(stdout, "1 %d\n", x);
        fflush(stdout);
    }
    x++;
    pid1 = getpid();
    fprintf(file_out, "%d %d\n", pid1, x);
    fflush(file_out);
    kill(pid2, SIGUSR1);
}

int
main(int argc, char **argv)
{
    signal(SIGUSR1, handl);
    int pid1, pid2;
    max_value = atoi(argv[1]);
    if (max_value <= 1) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    pipe(fd);
    if (!(pid1 = fork())) {
        signal(SIGUSR1, handl);
        while (1) {
            pause();
        }
    }
    if (!(pid2 = fork())) {
        signal(SIGUSR1, handl);
        while (1) {
            pause();
        }
    }
    FILE *file_in = fdopen(fd[0], "r");
    FILE *file_out = fdopen(fd[1], "w");
    int x = 1;
    fprintf(file_out, "%d %d\n", pid2, x);
    fflush(file_out);
    kill(pid1, SIGUSR1);
    fclose(file_out);
    fclose(file_in);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    fflush(stdout);
    return 0;
}
