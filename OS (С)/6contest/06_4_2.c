#include <stdio.h>
// fprintf printf
#include <dirent.h>
// readdir, opendir, closedir
#include <sys/types.h>
#include <sys/stat.h>
// lstat
#include <limits.h>
// PATH_MAX
#include <string.h>
// strlen
#include <stdlib.h>
// calloc, free, strtol
#include <unistd.h>
// access
#include <errno.h>
// error control

void
normalize_path(char *path)
{
    int size = strlen(path);
    if (size > 1 && path[size - 1] == '/') {
        path[size - 1] = 0;
    }
}

void
get_files(long int limit, int lev, char *directory, char *relative)
{
    if (lev > 4) {
        return;
    }
    DIR *d = opendir(directory);
    if (!d) {
        exit(1);
    }
    struct dirent *dd;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        struct stat stbuf;
        char path[PATH_MAX];
        int n = snprintf(path, sizeof(path), "%s/%s", directory, dd->d_name);
        if (n >= sizeof(path) || n < 0) {
            continue;
        }
        if (lstat(path, &stbuf) < 0) {
            continue;
        }
        if (S_ISREG(stbuf.st_mode) && (access(path, R_OK) == 0) && (stbuf.st_size <= limit)) {
            printf("%s%s\n", relative, dd->d_name);
        } else if (S_ISDIR(stbuf.st_mode)) {
            char new_rel[PATH_MAX];
            snprintf(new_rel, sizeof(new_rel), "%s%s/", relative, dd->d_name);
            get_files(limit, lev + 1, path, new_rel);
        }
    }
    closedir(d);
}

int
main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "wrong arguements\n");
        exit(1);
    }
    normalize_path(argv[1]);
    char *eptr = argv[2];
    long int limit = strtol(argv[2], &eptr, 10);
    if (errno || *eptr) {
        fprintf(stderr, "wrong arguements\n");
        exit(1);
    }
    get_files(limit, 1, argv[1], "");
    return 0;
}