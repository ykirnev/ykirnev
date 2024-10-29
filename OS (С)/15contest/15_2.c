#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

volatile sig_atomic_t value = 0;
volatile sig_atomic_t flag = 0;

void
handlusr(int sig)
{
    signal(SIGUSR1, handlusr);
    signal(SIGUSR2, handlusr);
    if (sig == SIGUSR1) {
        flag = 0;
        value = 0;
    } else if (sig == SIGUSR2) {
        flag = 0;
        value = 1;
    }
}

void
handlcio(int sig)
{
    signal(SIGIO, handlcio);
    if (sig == SIGIO) {
        exit(EXIT_SUCCESS);
    }
}

void
handlalarm(int sig)
{
    signal(SIGALRM, handlalarm);
    if (sig == SIGALRM) {
        flag = 1;
    }
}

int
main(int argc, char *argv[])
{
    signal(SIGALRM, SIG_IGN);
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == -1) {
        _exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        signal(SIGUSR1, handlusr);
        signal(SIGUSR2, handlusr);
        signal(SIGIO, handlcio);
        unsigned char answer = 0;
        int tmp_offset = 0;
        flag = 1;
        while (1) {
            while (flag != 0)
                ;
            answer = answer << 1 | value;
            tmp_offset++;
            if (tmp_offset == 8) {
                tmp_offset = 0;
                printf("%c", answer);
                fflush(stdout);
                answer = 0;
            }
            flag = 1;
            kill(0, SIGALRM);
        }
    }
    pid2 = fork();
    if (pid2 == -1) {
        _exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        signal(SIGALRM, handlalarm);
        unsigned char buf = 0;
        int fd = open(argv[1], O_RDONLY);
        while (read(fd, &buf, 1) > 0) {
            for (int i = 0; i < 8; i++) {
                if (((buf >> (7 - i)) & 1) == 0) {
                    flag = 0;
                    kill(pid1, SIGUSR1);
                } else {
                    flag = 0;
                    kill(pid1, SIGUSR2);
                }
                while (flag != 1)
                    ;
            }
        }
        close(fd);
        kill(pid1, SIGIO);
        _exit(EXIT_SUCCESS);
    }
    wait(NULL);
    wait(NULL);
    return 0;
}
