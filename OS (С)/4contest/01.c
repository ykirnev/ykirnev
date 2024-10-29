#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

enum
{
    SHIFT_FOR_BYTE_0 = 20,
    SHIFT_FOR_BYTE_1 = 12,
    MASK_FOR_BYTE_1 = 0x000FF000,
    SHIFT_FOR_BYTE_2 = 8,
    MASK_FOR_BYTE_2 = 0x00000F00,
    MASK_FOR_BYTE_3 = 0x000000FF,
    SIZE_BUF = 4
};

int 
main(int argc, char *argv[]) 
{
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    unsigned int input;
    while (scanf("%u", &input) ) {
        char buf_out[SIZE_BUF];
        buf_out[0] = input >> SHIFT_FOR_BYTE_0;
        buf_out[1] = (input & MASK_FOR_BYTE_1) >> SHIFT_FOR_BYTE_1;
        buf_out[2] = (input & MASK_FOR_BYTE_2) >> SHIFT_FOR_BYTE_2;
        buf_out[3] = input & MASK_FOR_BYTE_3;
        write(fd, buf_out, sizeof(buf_out));
    }
    close(fd);
    return 0;
}