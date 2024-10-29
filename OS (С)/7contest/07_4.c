#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    BITE_SIZE = 8
};

int
main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDWR, 0600);
    if (fd1 == -1) {
        return 0;
    }
    int size_file = lseek(fd1, 0, SEEK_END);
    if (size_file < 1) {
        return 0;
    }
    lseek(fd1, 0, SEEK_SET);
    int id;
    int id_abs;
    char buf;
    int read_flag;
    int write_flag;
    while (scanf("%d", &id) == 1) {
        id_abs = id;
        if (id < 0) {
            id_abs *= (-1);
        }
        if ((id_abs / BITE_SIZE > size_file) || (id_abs == 0)) {
            continue;
        }
        id_abs--;
        lseek(fd1, id_abs / BITE_SIZE, SEEK_SET);
        read_flag = read(fd1, &buf, sizeof(buf));
        if (read_flag != sizeof(buf)) {
            return 1;
        }
        if (id > 0) {
            buf |= (1 << (id_abs % BITE_SIZE));
        } else {
            buf &= ~(1 << (id_abs % BITE_SIZE));
        }
        lseek(fd1, id_abs / BITE_SIZE, SEEK_SET);
        write_flag = write(fd1, &buf, sizeof(buf));
        if (write_flag != sizeof(buf)) {
            return 1;
        }
    }
    close(fd1);
    return 0;
}
