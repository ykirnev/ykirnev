#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>

int
main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if (!fork()) {
            int dup_flag;
            int fd1 = open(argv[4], O_RDONLY);
            if (fd1 < 0) {
                return 1;
            }
            dup_flag = dup2(fd1, 0);
            if (dup_flag < 0) {
                return 1;
            }
            close(fd1);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else {
            int status;
            wait(&status);
            if ((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) {
                if (fork()) {
                    wait(NULL);
                } else {
                    execlp(argv[2], argv[2], NULL);
                    _exit(1);
                }
            }
        }
    } else {
        close(fd[1]);
        if (!fork()) {
            dup2(fd[0], 0);
            close(fd[0]);
            int dup_flag;
            int fd2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0660);
            if (fd2 < 0) {
                return 1;
            }
            dup_flag = dup2(fd2, 1);
            if (dup_flag < 0) {
                return 1;
            }
            close(fd2);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } else {
            close(fd[0]);
            wait(NULL);
            wait(NULL);
        }
    }
}
