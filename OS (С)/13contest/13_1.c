#include <time.h>
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
            if (!fork()) {
                time_t tmp = time(NULL);
                write(fd[1], &tmp, sizeof(tmp));
                write(fd[1], &tmp, sizeof(tmp));
                write(fd[1], &tmp, sizeof(tmp));
                return 0;
            } else {
                wait(NULL);
                close(fd[1]);
                time_t grandson_time;
                struct tm *grandson;
                read(fd[0], &grandson_time, sizeof(grandson_time));
                grandson = localtime(&grandson_time);
                printf("D:%02d\n", grandson->tm_mday);
                fflush(NULL);
                return 0;
            }
        } else {
            wait(NULL);
            close(fd[1]);
            time_t son_time;
            struct tm *son;
            read(fd[0], &son_time, sizeof(son_time));
            son = localtime(&son_time);
            printf("M:%02d\n", son->tm_mon + 1);
            fflush(NULL);
            return 0;
        }
    } else {
        wait(NULL);
        close(fd[1]);
        time_t father_time;
        struct tm *father;
        read(fd[0], &father_time, sizeof(father_time));
        father = localtime(&father_time);
        printf("Y:%04d\n", father->tm_year + 1900);
        fflush(NULL);
        return 0;
    }
}
