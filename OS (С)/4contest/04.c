#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

enum
{
    MASK_INT_3 = 0x000000FF,
    MASK_INT_2 = 0x0000FF00,
    MASK_INT_1 = 0x00FF0000,
    MASK_INT_0 = 0xFF000000,
    SHIFT_INT_3 = 24,
    SHIFT_INT_2 = 8,
    SHIFT_INT_1 = 8,
    SHIFT_INT_0 = 24
};

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

ssize_t
my_read(int fd, void *buf, size_t count)
{
    int tmp_read = 0;
    int read_flag = 1;
    while (tmp_read < count && (read_flag != 0)) {
        read_flag = read(fd, buf + tmp_read, count - tmp_read);
        if (read_flag == -1) {
            fprintf(stderr, "Error reading file.\n");
            return 1;
        }
        if (read_flag > 0) {
            tmp_read = tmp_read + read_flag;
        }
    }
    return 1;
}

int
btol(int input)
{
    unsigned int input_3 = MASK_INT_3 & input;
    unsigned int input_2 = MASK_INT_2 & input;
    unsigned int input_1 = MASK_INT_1 & input;
    unsigned int input_0 = MASK_INT_0 & input;
    unsigned int answer = input_3 << SHIFT_INT_3 | input_2 << SHIFT_INT_2;
    answer = answer | input_1 >> SHIFT_INT_1 | input_0 >> SHIFT_INT_0;
    return (int) answer;
}

void
recursion(int fd, int tmp_id)
{
    int32_t tmp_key;
    int32_t tmp_right;
    int32_t tmp_left;
    lseek(fd, tmp_id * sizeof(struct Node), SEEK_SET);
    my_read(fd, &tmp_key, sizeof(tmp_key));
    tmp_key = btol(tmp_key);
    my_read(fd, &tmp_left, sizeof(tmp_left));
    tmp_left = btol(tmp_left);
    my_read(fd, &tmp_right, sizeof(tmp_right));
    tmp_right = btol(tmp_right);
    if (tmp_right != 0) {
        recursion(fd, tmp_right);
    }
    printf("%d\n", tmp_key);
    if (tmp_left != 0) {
        recursion(fd, tmp_left);
    }
}

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    int size_file = lseek(fd, 0, SEEK_END);
    if (size_file < 1) {
        return 0;
    }
    recursion(fd, 0);
    close(fd);
    return 0;
}