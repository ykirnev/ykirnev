#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>

enum CONST
{
    mask1 = 0x0f,
    mask2 = 0xf0
};

int
main(int argc, char const *argv[])
{
    int begin_blok, offset, prev_block;
    scanf("%d %d", &begin_blok, &offset);

    int fd = open(argv[1], O_RDONLY, 0666);

    while (offset > 0)
    {
        prev_block = begin_blok;
        begin_blok++;
        int sdvig = begin_blok / 2 * 3;
        begin_blok = 0;
        unsigned char buf = 0;

        if (begin_blok % 2) {
            sdvig++;
            lseek(fd, sdvig, SEEK_SET);
            read(fd, &buf, sizeof(buf));
            begin_blok = (buf & mask1) << 8;
            lseek(fd, sdvig - 1, SEEK_SET);
            read(fd, &buf, sizeof(buf));
            begin_blok |= buf;
        } else {
            sdvig--;
            lseek(fd, sdvig, SEEK_SET);
            read(fd, &buf, sizeof(buf));
            begin_blok = (buf & mask2);
            lseek(fd, sdvig + 1, SEEK_SET);
            read(fd, &buf, sizeof(buf));
            begin_blok |= buf << 4;
        }
        if (begin_blok == 0xfff) {
            printf("0 0\n");
            return 0;
        }

        offset -= 512;
    }

    printf("%d %d", prev_block, offset + 512);

    return 0;
}


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <time.h>

int main(){
    int fd[2];
    pipe(fd);
    int deep;
    scanf("%d", &deep);
    printf("%d %d\n", getpid(), deep);
    if(!fork()){
        for(int i = 0; i < deep; i++){
            if(i == deep - 1){
                scanf("%d", &deep);
                printf("%d %d\n", getpid(), deep);
                write(fd[1], &deep, sizeof(deep));
                _exit(0);
            }
            if(fork()){
                while(wait(NULL) != -1){}
                _exit(0);
            }
            //printf("%d\n", i);
        }
    }
    while(wait(NULL) != -1){}
    int buf;
    while (read(fd[0], &buf, sizeof(buf)) > 0){
        if(!fork()){
            for(int i = 0; i < buf; i++){
                if(i == buf - 1){
                    if(scanf("%d", &deep) == EOF){
                        _exit(0);
                    }
                    printf("%d %d\n", getpid(), deep);
                    write(fd[1], &deep, sizeof(deep));
                    _exit(0);
                }
                if(fork()){
                    while(wait(NULL) != -1){}
                    _exit(0);
                }
                //printf("%d\n", i);
            }
        }
        while(wait(NULL) != -1){}
    }
    return 0;
}
