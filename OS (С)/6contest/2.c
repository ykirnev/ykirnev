#include <stdio.h>

void normalize_path(char *buf) {
    if (buf == NULL) {
        return;
    }
    int length = 0;
    int slash_count = 0; 
    while (buf[length] != '\0') {
        if (buf[length] == '/' && length == 0) {
            slash_count++;
        }
        length++;
    }
    int write_index = 0;
    int dot_count = 0;
    int start = slash_count;
    for (int i = start; i < length; i++) {
        if (buf[i] == '/') {
            if (dot_count == 1) {
                dot_count = 0;
            } else if (dot_count == 2) {
                write_index = start - 2;
                while (write_index >= slash_count && buf[write_index] != '/') {
                    write_index--;
                }
                dot_count = 0;
                start = write_index + 1;
            } else {
                for (int j = start; j <= i; j++) {
                    buf[write_index] = buf[j];
                    write_index++;
                }
                start = i + 1;
            }
        } else if (buf[i] == '.') {
            dot_count++;
        } else {
            dot_count = 0;
        }
    }
    if (write_index > slash_count)
        write_index--;
    buf[write_index] = '\0';
}

int main() {
    char path1[] = "/a/b/c/";
    normalize_path(path1);
    printf("%s\n", path1); 
    char path2[] = "/a/b/../";
    normalize_path(path2);
    printf("%s\n", path2);
    char path3[] = "/a/b/../../..";
    normalize_path(path3);
    printf("%s\n", path3);
    return 0;
}
