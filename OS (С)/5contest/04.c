#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int
my_strcmp(const void *str1, const void *str2)
{
    return strcmp(*(const char **) str1, *(const char **) str2);
}

int
main(int argc, char *argv[])
{
    char **mas_str = calloc(argc - 1, sizeof(char *));
    ino_t *mas_inode = calloc(argc - 1, sizeof(ino_t));
    int tmp_id = 0;
    struct stat *buf_stat = calloc(1, sizeof(struct stat));
    ino_t tmp_ino;
    int cmp_sign;
    int flag_of_change = 0;
    for (int i = 1; i < argc; i++) {
        if (access(argv[i], F_OK) == 0) {
            stat(argv[i], buf_stat);
            tmp_ino = buf_stat->st_ino;
            for (int j = 0; j < tmp_id; j++) {
                if (mas_inode[j] == tmp_ino) {
                    cmp_sign = strcmp(mas_str[j], argv[i]);
                    if (cmp_sign < 0) {
                        mas_str[j] = argv[i];
                    }
                    flag_of_change = 1;
                    break;
                }
            }
            if (flag_of_change != 1) {
                mas_str[tmp_id] = calloc(1, sizeof(char *));
                mas_str[tmp_id] = argv[i];
                mas_inode[tmp_id] = tmp_ino;
                tmp_id = tmp_id + 1;
            }
            flag_of_change = 0;
        }
    }
    qsort(mas_str, tmp_id, sizeof(mas_str[0]), my_strcmp);
    for (int i = 0; i < tmp_id; i++) {
        printf("%s\n", mas_str[i]);
    }
    free(mas_str);
    free(mas_inode);
    free(buf_stat);
    return 0;
}