#include <stdio.h>
#include <stdlib.h>
enum
{
    SLASH_POINT_SHIFT = 2,
    HOME_DIR_SHIFT = 3
};

void
normalize_path(char *buf)
{
    if (buf[0] == '\0') {
        return;
    }
    int len = 0;
    while (buf[len] != '\0') {
        len++;
    }
    int k;
    int i_new = 0;
    int j;
    for (int i = 0;  buf[i] != '\0'; i++) {
        if ((len > (i + 1)) && (buf[i] == '/' && buf[i + 1] == '.')) {
            if (buf[i + SLASH_POINT_SHIFT] == '/' || buf[i + SLASH_POINT_SHIFT] == '\0') {
                for (j = i; buf[j + SLASH_POINT_SHIFT] != '\0'; j++) {
                    buf[j] = buf[j + SLASH_POINT_SHIFT];
                }
                buf[j] = '\0';
                i--;
                len = len - SLASH_POINT_SHIFT;
                continue;
            }
        }
        if ((len > (i + SLASH_POINT_SHIFT)) && (buf[i] == '/') && (buf[i + 1] == '.') &&
            (buf[i + SLASH_POINT_SHIFT] == '.') &&
            (buf[i + HOME_DIR_SHIFT] == '/' || buf[i + HOME_DIR_SHIFT] == '\0')) {
            k = i - 1;
            while ((k >= 0) && (buf[k] != '/')) {
                k--;
            }
            if (k < 0) {
                k = 0;
            }
            i_new = k - 1;
            for (j = i + 3; buf[j] != '\0'; j++) {
                buf[k] = buf[j];
                k++;
            }
            buf[k] = '\0';
            i = i_new;
        }
        i_new = i;
    }
    if (i_new < 1) {
        buf[0] = '/';
        buf[1] = '\0';
        return;
    }
    if (buf[i_new] == '/') {
        buf[i_new] = '\0';
    }
    return;
}

int
main()
{
    char *path = calloc(100, sizeof(char));
    //sprintf(path, "/././.././../../a/b/../be/././../pizdec/./././../../suka_na_ure/././../../lost/././././../.../.././../win/./././");
    sprintf(path, "/aa>");
    printf("Input: %s\n", path);
    normalize_path(path);
    printf("Result: %s\n", path);
    return 0;
}
