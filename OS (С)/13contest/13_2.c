#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            close(fd[1]);
            int x;
            long long sum = 0;
            int read_flag = 1;
            while (read_flag > 0) {
                read_flag = read(fd[0], &x, sizeof(x));
                if (read_flag != sizeof(x)) {
                    read_flag = 0;
                    break;
                }
                sum = sum + x;
            }
            printf("%lld\n", sum);
            close(fd[0]);
            return 0;
        } else {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            return 0;
        }
    } else {
        int x;
        int scanf_flag = 1;
        while (scanf_flag == 1) {
            scanf_flag = scanf("%d", &x);
            if (scanf_flag != 1) {
                scanf_flag = 0;
                break;
            }
            write(fd[1], &x, sizeof(x));
        }
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        return 0;
    }
}