#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int
parse_rwx_permissions(const char *str) {
    unsigned sum = 0;
    int three = 1 << 1 | 1;
    int eight = 1 << three;
    int nine = eight | 1; 
    const char buf[] = "rwxrwxrwx";
    int len = sizeof(buf) - 1;
    if (str == NULL) {
        return -1;
    }
    if (strlen(str) != len) {
        return -1;
    }
    for(int i = 0; i < len; i++) {
        sum = sum << 1;
        if (str[i] == buf[i]) {
            sum = sum | 1;
        } else if (str[i] != '-') {
            return -1;
        }     
    }
    return sum;
}