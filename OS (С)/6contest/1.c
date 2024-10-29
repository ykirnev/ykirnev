#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

enum
{
    SUFFIX_LEN = sizeof(".exe") - 1
};

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        exit(1);
    }
    DIR *d = opendir(argv[1]);
    if (!d) {
        exit(1);
    }
    const char *FLAG = ".exe";
    struct dirent *dd;
    long long count = 0;
    int flag = 0;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        char path[PATH_MAX];
        flag = snprintf(path, sizeof(path), "%s/%s", argv[1], dd->d_name);
        if (flag != sizeof(path)) {
            continue;
        }
        struct stat stb;
        if (access(path, X_OK)) {
            continue;
        if (stat(path, &stb) < 0) {
            continue;
        }
        if (!S_ISREG(stb.st_mode)) {
            continue;
        }
        size_t name_len = strlen(dd->d_name);
        if (name_len < SUFFIX_LEN) {
            continue;
        }
        if (strcmp(dd->d_name + name_len - SUFFIX_LEN, FLAG) == 0) {
            count++;
        }
    }
    closedir(d);
    printf("%lld\n", count);
    return 0;
}