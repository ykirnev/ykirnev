#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *normalize(const char *path) {
    char *slash = "/";
    if (path == NULL || *path == '\0') {
        return NULL;
    }
    if ((strlen(path) == 2) && (path[0] == '/') && path[1] == '.') {
        return slash;
    }
    if ((strlen(path) == 3) && (path[0] == '/') && path[1] == '.' && path[2] == '.') {
        return slash;
    }
    char *normalized = (char *)malloc(strlen(path) + 2); 
    int len = 0;
    int skip = 0;
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '/') {
            i += 1;
            continue;
        } else if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.' && (path[i + 3] == '/' || path[i + 3] == '\0')) {
            i += 2;
            if (len > 0) {
                while (len > 0 && normalized[len - 1] != '/') {
                    len = len - 1;
                }
                len = len - 1;
            }
            if (path[i] == '\0') {
                break;
            }
        } else {
            normalized[len++] = path[i];
        }
    }
    if (normalized[len - 1] != '/') {
        normalized[len++] = '/';
    }
    if ((normalized[len - 1] == '/') && (normalized[len - 2] == '.') && (normalized[len - 3] == '/')) {
        normalized[len - 2] = '\0';
        normalized[len - 1] = '\0';
    }
    normalized[len] = '\0';
    len = strlen(normalized);
    if (len > 1) {
        normalized[len - 1] = '\0';
    }
    return normalized;
}

int main() {
    const char *input_path = "/a/./fwdwb/../c/dwec";
    char *normalized_path = normalize(input_path);

    char *tests[] = {"/.",
                 "/",
                 "/b/d/..",
                 "/..",
                 "/a/a/a/./../.",
                 "/./a/b/c/..",
                 "/./a/./c/..",
                 "/a/./../b/.././c/././..",
                 "/../../../a/b/c",
                 "/a/b/../../abc",
                 "/a/b/../abc/.",
                 "/./.././../as/./../asdv/.././safdsd/gfd/./../dfs/./gfd/.."};
    for (int i = 0; i <= 11; ++i) {
        printf("%s\n", normalize(tests[i]));
    }
    return 0;
}
