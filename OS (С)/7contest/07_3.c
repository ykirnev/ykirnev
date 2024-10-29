#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

int
check_path(char *dir, char *name, ino_t prev_inode)
{
    int flag;
    DIR *d = opendir(dir);
    if (!d) {
        return 0;
    }
    struct dirent *dd;
    struct stat st;
    char full_path[PATH_MAX];
    int len_start = strlen(dir) + 1;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        flag = snprintf(full_path, sizeof(full_path), "%s/%s", dir, dd->d_name);
        if ((flag < sizeof(full_path)) && (stat(full_path, &st) >= 0)) {
            if ((strcmp(full_path + len_start, name) == 0) && (prev_inode == st.st_ino)) {
                return 1;
            }
        }
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        return 0;
    }
    int flag;
    DIR *d = opendir(argv[1]);
    if (!d) {
        return 0;
    }
    struct dirent *dd;
    struct stat st;
    char full_path[PATH_MAX];
    long long size = 0;
    long long tmp_size = 0;
    int len_start = strlen(argv[1]) + 1;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        flag = snprintf(full_path, sizeof(full_path), "%s/%s", argv[1], dd->d_name);
        if ((flag < sizeof(full_path)) && (lstat(full_path, &st) >= 0)) {
            if ((!S_ISLNK(st.st_mode)) && (S_ISREG(st.st_mode)) && (!access(full_path, W_OK))) {
                tmp_size = st.st_size;
                if (check_path(argv[2], full_path + len_start, st.st_ino) == 1) {
                    size += tmp_size;
                }
            }
        }
    }
    printf("%lld\n", size);
}
