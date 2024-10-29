#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

enum
{
    KB_size = 1024
};

int
main(int argc, char *argv[])
{
    struct stat stbuf;
    long long sum = 0;
    int stat_flag;
    for (int i = 1; i < argc; i++) {
        if (access(argv[i], F_OK) == 0) {
            stat_flag = lstat(argv[i], &stbuf);
            if (stat_flag == -1) {
                continue;
            }
            if (((stbuf.st_size) % KB_size == 0) && S_ISREG(stbuf.st_mode)) {
                if (!(S_ISLNK(stbuf.st_mode)) && (stbuf.st_nlink == 1)) {
                    sum = sum + stbuf.st_size;
                }
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}