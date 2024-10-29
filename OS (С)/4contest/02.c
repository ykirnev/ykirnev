#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int n;
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 0;
    }
    int size_file = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    size_file = size_file / sizeof(double);
    if (size_file < 2) {
        return 0;
    }
    int scanf_check = sscanf(argv[2], "%d", &n);
    if (scanf_check == -1) {
        return 0;
    }
    if (n < 1) {
        return 0;
    }
    double buf1, buf2;
    read(fd, &buf1, sizeof(double));
    n = n - 1;
    size_file = size_file - 1;
    while ((size_file > 0) && (n > 0)) {
        read(fd, &buf2, sizeof(double));
        lseek(fd, -sizeof(double), SEEK_CUR);
        buf2 = buf2 - buf1;
        write(fd, &buf2, sizeof(double));
        buf1 = buf2;
        n = n - 1;
        size_file = size_file - 1;
    }
    close(fd);
    return 0;
}