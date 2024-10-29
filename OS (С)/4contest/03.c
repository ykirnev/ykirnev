#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 0;
    }
    long long min_tmp;
    long long min_tmp_id;
    long long buf;
    int size_file = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    size_file = size_file / sizeof(long long);
    if (size_file < 1) {
        return 0;
    }
    read(fd, &buf, sizeof(long long));
    size_file = size_file - 1;
    min_tmp = buf;
    min_tmp_id = lseek(fd, -sizeof(long long), SEEK_CUR);
    lseek(fd, sizeof(long long), SEEK_CUR);
    while (size_file > 0) {
        read(fd, &buf, sizeof(long long));
        size_file = size_file - 1;
        if (buf < min_tmp) {
            min_tmp = buf;
            min_tmp_id = lseek(fd, -sizeof(long long), SEEK_CUR);
            lseek(fd, sizeof(long long), SEEK_CUR);
        }
    }
    if (min_tmp == LLONG_MIN){
        close(fd);
        return 0;
    }
    lseek(fd, min_tmp_id, SEEK_SET);
    min_tmp = -min_tmp;
    write(fd, &min_tmp, sizeof(long long));
    close(fd);
    return 0;
}