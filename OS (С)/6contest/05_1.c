#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

ssize_t
getcwd2(int fd, char *buf, size_t size)
{
    DIR *main_dp = opendir(".");
    if (!main_dp) {
        return -1;
    }
    int main_fd = dirfd(main_dp);
    if (main_fd == -1) {
        closedir(main_dp);
        return -1;
    }
    if (fchdir(fd) == -1) {
        closedir(main_dp);
        return -1;
    }
    struct stat cur_dir, prev_dir;
    if (lstat(".", &cur_dir) == -1) {
        fchdir(main_fd);
        closedir(main_dp);
        return -1;
    }
    char path[PATH_MAX + NAME_MAX];
    char prev_path[PATH_MAX];
    path[0] = '\0';
    memset(&prev_dir, 0, sizeof(prev_dir));
    int new_fd;
    DIR *new_dir = 0;
    struct dirent *d;
    while (cur_dir.st_ino != prev_dir.st_ino  cur_dir.st_dev != prev_dir.st_dev) {
        memcpy(&prev_dir, &cur_dir, sizeof(prev_dir));
        if (new_dir) {
            if (closedir(new_dir) < 0) {
                fchdir(main_fd);
                closedir(main_dp);
                return -1;
            }
        }
        if (chdir("..") == -1) {
            fchdir(main_fd);
            closedir(main_dp);
            return -1;
        }
        new_dir = opendir(".");
        if (!new_dir) {
            fchdir(main_fd);
            closedir(main_dp);
            return -1;
        }
        while ((d = readdir(new_dir))) {
            if (!S_ISDIR(cur_dir.st_mode)) {
                continue;
            }
            if (d->d_ino == prev_dir.st_ino) {
                if (!strcmp(d->d_name, "..")  !strcmp(d->d_name, ".")) {
                    continue;
                }
                strcpy(prev_path, path);
                if (!strcmp(prev_path, "")) {
                    snprintf(path, PATH_MAX + NAME_MAX + 1, "%s%s", d->d_name, prev_path);
                } else {
                    snprintf(path, PATH_MAX + NAME_MAX + 1, "%s%s%s", d->d_name, "/", prev_path);
                }
                new_fd = dirfd(new_dir);
                if (new_fd == -1) {
                    closedir(new_dir);
                    fchdir(main_fd);
                    closedir(main_dp);
                    return -1;
                }
                if (lstat(".", &cur_dir) == -1) {
                    closedir(new_dir);
                    fchdir(main_fd);
                    closedir(main_dp);
                    return -1;
                }
                break;
            }
        }
    }
    if (new_dir) {
        if (closedir(new_dir) == -1) {
            fchdir(main_fd);
            closedir(main_dp);
            return -1;
        }
    }
    char new_path[PATH_MAX + NAME_MAX + 2];
    snprintf(new_path, PATH_MAX + NAME_MAX + 1, "/%s", path);
    int cur_len = strlen(new_path);
    new_path[cur_len] = '\0';
    size_t end_size = (size - 1 < cur_len ? size - 1 : cur_len);
    if (size > 0) {
        if (size > 1) {
            snprintf(buf, end_size + 1, "%s", new_path);
            buf[end_size + 1] = '\0';
        } else {
            buf[0] = '\0';
        }
    }
    if (fchdir(main_fd) == -1) {
        if (new_dir) {
            closedir(new_dir);
        }
        closedir(main_dp);
        return -1;
    }
    if (closedir(main_dp) == -1) {
        return -1;
    }
    return cur_len;
}