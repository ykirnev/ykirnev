#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

ssize_t
getcwd2(int fd, char *buf, size_t size)
{
    struct stat st;
    struct dirent *dd;
    char full_path[PATH_MAX] = "";
    char tmp_full[PATH_MAX] = "";
    char prev_full_path[PATH_MAX] = "";
    DIR *d_start = opendir(".");
    if (!d_start) {
        return -1;
    }
    int start_fd = dirfd(d_start);
    int flag = fchdir(fd);
    if (flag < 0) {
        closedir(d_start);
        return -1;
    }
    flag = fstat(fd, &st);
    if (flag < 0) {
        fchdir(start_fd);
        closedir(d_start);
        return -1;
    }
    ino_t our_inode = st.st_ino;
    dev_t our_dev = st.st_dev;
    DIR *d = opendir("..");
    if (!d) {
        fchdir(start_fd);
        closedir(d_start);
        return -1;
    }
    chdir("..");
    int while_end_flag = 1;
    while (while_end_flag) {
        while ((dd = readdir(d))) {
            if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
                continue;
            }
            flag = snprintf(tmp_full, sizeof(full_path), "%s/%s", dd->d_name, prev_full_path);
            if (flag > PATH_MAX) {
                closedir(d);
                fchdir(start_fd);
                closedir(d_start);
                return -1;
            }
            if (lstat(tmp_full, &st) < 0) {
                continue;
            }
            if ((st.st_ino == our_inode) && (st.st_dev == our_dev)) {
                break;
            }
        }
        if (dd == NULL) {
            while_end_flag = 0;
            break;
        }
        flag = snprintf(full_path, sizeof(full_path), "%s/%s", dd->d_name, prev_full_path);
        if (flag > PATH_MAX) {
            closedir(d);
            fchdir(start_fd);
            closedir(d_start);
            return -1;
        }
        for (int i = 0; full_path[i] != '\0'; i++) {
            prev_full_path[i] = full_path[i];
        }
        closedir(d);
        d = opendir("..");
        if (!d) {
            fchdir(start_fd);
            closedir(d_start);
            return -1;
        }
        int prev_dir_fd = dirfd(d);
        if (prev_dir_fd < 0) {
            closedir(d);
            fchdir(start_fd);
            closedir(d_start);
            return -1;
        }
        flag = fstat(prev_dir_fd, &st);
        if (flag < 0) {
            closedir(d);
            fchdir(start_fd);
            closedir(d_start);
            return -1;
        }
        chdir("..");
    }
    closedir(d);
    fchdir(start_fd);
    closedir(d_start);
    int path_len = strlen(full_path) + 1;
    if (path_len != 1) {
        path_len--;
    }
    if (path_len == 1) {
        full_path[0] = '\0';
    }
    unsigned int size_int = (int) size;
    if (size_int == 0) {
        return (ssize_t) path_len;
    }
    if (size_int == 1) {
        buf[0] = '\0';
        return (ssize_t) path_len;
    }
    buf[0] = '/';
    if (size_int > path_len) {
        size_int = path_len + 1;
    }
    snprintf(buf + 1, size_int - 1, "%s", full_path);
    return (ssize_t) path_len;
}

int
main(void)
{
    int fd = open("/Users/ykirnev", O_RDONLY);
    char buf[120] = "";
    ssize_t result = getcwd2(fd, buf, 13332);
    printf("%s\n", buf);
    printf("%ld", result);
    close(fd);
}
