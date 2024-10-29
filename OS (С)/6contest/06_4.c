#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

enum
{
    MAX_RECURSION_DEPTH = 4,
    CORRECT_ARGC_VALUE = 3,
    MAX_SIZE_POSITION = 2
};

void
calc_dir(const char *path, int depth, long long int Z, int len_start)
{
    if (depth >= MAX_RECURSION_DEPTH) {
        return;
    }
    DIR *d = opendir(path);
    if (!d) {
        return;
    }
    struct dirent *dd;
    struct stat st;
    int flag;
    char full_path[PATH_MAX];
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        flag = snprintf(full_path, sizeof(full_path), "%s/%s", path, dd->d_name);
        if ((flag < sizeof(full_path)) && (lstat(full_path, &st) >= 0)) {
            if (S_ISDIR(st.st_mode)) {
                calc_dir(full_path, depth + 1, Z, len_start);
            } else if ((!S_ISLNK(st.st_mode)) && (S_ISREG(st.st_mode)) && (!access(full_path, R_OK)) &&
                       (st.st_size <= Z)) {
                printf("%s\n", full_path + len_start);
            }
        }
    }
    closedir(d);
}

int
main(int argc, char *argv[])
{
    if (argc != CORRECT_ARGC_VALUE) {
        exit(1);
    }
    long long Z;
    sscanf(argv[MAX_SIZE_POSITION], "%lld", &Z);
    int len_start = strlen(argv[1]) + 1;
    calc_dir(argv[1], 0, Z, len_start);
}
