#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void
func_close(int fd[2][2], int id, int max)
{
    if (id > 1) {
        close(fd[(id - 1) % 2][0]);
        close(fd[(id - 1) % 2][1]);
    }
    if (id != max - 1) {
        close(fd[id % 2][0]);
        close(fd[id % 2][1]);
    }
}

int
main(int argc, char **argv)
{
    int fd[2][2];
    pid_t pid[argc];
    int id_ignored;
    int kill_flag = 0;
    for (int i = 1; i < argc; i++) {
        if (i > 2) {
            close(fd[i % 2][0]);
            close(fd[i % 2][1]);
        }
        if (i != argc - 1) {
            pipe(fd[i % 2]);
        }
        pid[i] = fork();
        if (pid[i] == -1) {
            kill_flag = 1;
            id_ignored = i;
            break;
        } else if (pid[i] == 0) {
            if (argc > 2) {
                if (i != 1) {
                    dup2(fd[(i - 1) % 2][0], 0);
                }
                if (i != argc - 1) {
                    dup2(fd[i % 2][1], 1);
                }
            }
            func_close(fd, i, argc);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }
    }
    if (kill_flag == 1) {
        func_close(fd, id_ignored, argc);
        for (int j = 1; j < id_ignored; j++) {
            kill(pid[j], SIGKILL);
        }
        while (wait(NULL) > 0)
            ;
        return 1;
    }
    close(fd[argc % 2][0]);
    close(fd[argc % 2][1]);
    while (wait(NULL) > 0)
        ;
    return 0;
}
