#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct tm* gettime(int fd[2])
{
    wait(NULL);
    close(fd[1]);
    time_t c_time;
    read(fd[0], &c_time, sizeof(c_time));
    return localtime(&c_time);
}

int main(void) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            if (!fork()) {
                close(fd[0]);
                time_t c_time = time(NULL);
                for (int i = 0; i < 3; i++) {
                    write(fd[1], &c_time, sizeof(c_time));
                }
                return 0;
            } else {
                printf("D:%d\n", gettime(fd)->tm_mday);
                fflush(stdout);
                return 0;
            }
        } else {
            printf("M:%d\n", gettime(fd)->tm_mon + 1);
            fflush(stdout);
            return 0;
        }
    } else {
        printf("Y:%d\n", gettime(fd)->tm_year + 1900);
        fflush(stdout);
        return 0;
    }
}





#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            close(fd[1]);
            long long sum = 0;
            int tmp;
            while (read(fd[0], &tmp, sizeof(tmp)) == sizeof(tmp)) {
                sum += tmp;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            close(fd[0]);
            return 0;
        } else {
            close(fd[1]);
            close(fd[0]);
            wait(NULL);
            return 0;
        }
    } else {
        close(fd[0]);
        int tmp;
        while (scanf("%d", &tmp) == 1) {
            if (write(fd[1], &tmp, sizeof(tmp)) != sizeof(tmp)) {
                return 1;
            }
        }
        close(fd[1]);
        wait(NULL);
        return 0;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int
main(void)
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        close(fd[1]);
        if (!fork()) {
            long long sum = 0;
            int tmp;
            while (read(fd[0], &tmp, sizeof(tmp)) > 0)  {
                sum += tmp;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            exit(0);
        }
        else {
            wait(NULL);
            exit(0);
        }
    }
    else {
        int tmp;
        close(fd[0]);
        while (scanf("%d", &tmp) == 1) {
            write(fd[1], &tmp, sizeof(tmp));
        }
        close(fd[1]);
        wait(NULL);
        exit(0);
    }
    return 0;
}



#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        return 1;
    }
    int fd[2];
    pipe(fd);
    if (!fork()) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        if (!fork()) {
            int file1 = open(argv[4], O_RDONLY);
            if (file1 < 0) {
                _exit(1);
            }
            dup2(file1, 0);
            close(file1);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                if (!fork()) {
                    execlp(argv[2], argv[2], NULL);
                    _exit(1);
                } else {
                    wait(NULL);
                }
            }
            return 0;
        }
    } else {
        if (!fork()) {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            int file2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
            if (file2 < 0) {
                return 1;
            }
            dup2(file2, 1);
            close(file2);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } else {
            close(fd[1]);
            close(fd[0]);
            while(wait(NULL) != -1);
        }
        return 0;
    }
}



#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void son(int *wpipe, int *rpipe, int id, int max)
{
    close(wpipe[0]);
    close(rpipe[1]);
    FILE *out = fdopen(wpipe[1], "w");
    FILE *in = fdopen(rpipe[0], "r");
    int num;
    fflush(in);
    while (fscanf(in, "%d", &num) == 1 && num != max) {
        printf("%d %d\n", id, num++);
        fflush(stdout);
        if (num >= max) {
            _exit(0);
        }
        fprintf(out, "%d\n", num);
        fflush(out);
    }
    fclose(out);
    fclose(in);
    _exit(0);
}

int main(int argc, char *argv[])
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    FILE *start = fdopen(fd2[1], "w");
    fprintf(start, "1\n");
    fflush(start);
    int max = atoi(argv[1]);

    if (!fork()) {
        son(fd1, fd2, 1, max);
    }
    if (!fork()) {
        son(fd2, fd1, 2, max);
    }
    close(fd1[1]);
    close(fd2[1]);
    close(fd2[0]);
    close(fd1[0]);
    while(wait(NULL) != -1);
    printf("Done\n");
    fflush(stdout);
    fclose(start);
    return 0;
}