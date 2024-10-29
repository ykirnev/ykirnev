#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    long long sum = 0;
    int sum_print;
    long long tmp_id = 0;
    int read_flag;
    int write_flag;
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        return 0;
    }
    int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0600);
    if (fd2 == -1) {
        return 0;
    }
    int mod;
    sscanf(argv[3], "%d", &mod);
    int size_file = lseek(fd1, 0, SEEK_END);
    if (size_file < 1) {
        return 0;
    }
    lseek(fd1, 0, SEEK_SET);
    unsigned char buf;
    char existence;
    while (size_file > 0) {
        read_flag = read(fd1, &buf, sizeof(buf));
        if (read_flag != sizeof(buf)) {
            return 1;
        }
        for (int i = 0; i < CHAR_BIT; i++) {
            tmp_id = (tmp_id + 1) % mod;
            sum = (sum + tmp_id * tmp_id) % mod;
            existence = buf & 1;
            if (existence == 1) {
                sum_print = (int) sum % mod;
                write_flag = write(fd2, &sum_print, sizeof(sum_print));
                if (write_flag != sizeof(sum_print)) {
                    return 1;
                }
            }
            buf = buf >> 1;
        }
        size_file = size_file - 1;
    }
    close(fd1);
    close(fd2);
    return 0;
}