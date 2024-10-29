#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum
{
    FIRST_BYTE = 8,
    SECOND_BYTE = 16,
    THIRD_BYTE = 24,
    KEY = 0,
    LEFT_IND = 1,
    RIGHT_IND = 2,
    STRUCT_SIZE = 3,
    INT_SIZE = 4,
    FIRST_BYTE_INDEX = 1,
    SECOND_BYTE_INDEX = 2,
    THIRD_BYTE_INDEX = 3
};

ssize_t
my_read(int fd, void *buf, size_t count)
{
    size_t c = 0;
    while (c != count) {
        ssize_t ch = read(fd, buf + c, count - c);
        if (ch == -1) {
            fprintf(stderr, "Error of reading\n");
            exit(1);
        } else if (ch == 0) {
            break;
        }
        c += ch;
    }
    return (ssize_t) c;
}

void
little(int32_t *mas)
{
    unsigned char t[INT_SIZE];
    for (int i = 0; i < INT_SIZE - 1; i++) {
        t[0] = mas[i] >> THIRD_BYTE;
        t[FIRST_BYTE_INDEX] = mas[i] >> SECOND_BYTE;
        t[SECOND_BYTE_INDEX] = mas[i] >> FIRST_BYTE;
        t[THIRD_BYTE_INDEX] = mas[i];
        mas[i] = (t[THIRD_BYTE_INDEX] << THIRD_BYTE) | (t[SECOND_BYTE_INDEX] << SECOND_BYTE) |
                 (t[FIRST_BYTE_INDEX] << FIRST_BYTE) | t[0];
    }
}

void
travel(int32_t *root, int fd)
{
    if (root[RIGHT_IND] != 0) {
        int32_t mas[STRUCT_SIZE];
        if (lseek(fd, STRUCT_SIZE * sizeof(mas[0]) * root[RIGHT_IND], SEEK_SET) == (off_t) (-1)) {
            fprintf(stderr, "ERROR\n");
            exit(1);
        }
        if (my_read(fd, mas, STRUCT_SIZE * sizeof(mas[0])) != (size_t) STRUCT_SIZE * sizeof(mas[0])) {
            fprintf(stderr, "ERROR\n");
            exit(1);
        }
        little(mas);
        travel(mas, fd);
    }
    fprintf(stdout, "%d\n", root[KEY]);
    if (root[LEFT_IND] != 0) {
        int32_t mas[STRUCT_SIZE];
        if (lseek(fd, STRUCT_SIZE * sizeof(mas[0]) * root[LEFT_IND], SEEK_SET) == (off_t) (-1)) {
            fprintf(stderr, "ERROR\n");
            exit(1);
        }
        if (my_read(fd, mas, STRUCT_SIZE * sizeof(mas[0])) != (size_t) STRUCT_SIZE * sizeof(mas[0])) {
            fprintf(stderr, "ERROR\n");
            exit(1);
        }
        little(mas);
        travel(mas, fd);
    }
}

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (!lseek(fd, 0, SEEK_END)) {
        close(fd);
        return 0;
    }
    if (lseek(fd, 0, SEEK_SET) == (off_t) (-1)) {
        fprintf(stderr, "ERROR\n");
        exit(1);
    }
    int32_t mas[STRUCT_SIZE];
    if (my_read(fd, mas, STRUCT_SIZE * sizeof(mas[0])) != (size_t) STRUCT_SIZE * sizeof(mas[0])) {
        fprintf(stderr, "ERROR\n");
        exit(1);
    }
    little(mas);
    travel(mas, fd);
    close(fd);
    return 0;
}