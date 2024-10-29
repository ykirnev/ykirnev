#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    BASE = 10
};

void *
no_code_duplicate(FILE *fin, FILE *fout, int stop, int id)
{
    int x = 1;
    int flag = 1;
    int scanf_flag;
    setbuf(fin, NULL);
    setbuf(fout, NULL);
    while (flag == 1) {
        scanf_flag = fscanf(fin, "%d", &x);
        fflush(fin);
        if (scanf_flag == 1 && x < stop) {
            printf("%d %d\n", id, x);
            fflush(stdout);
            x++;
            fprintf(fout, "%d\n", x);
        } else if (x >= stop) {
            flag = 0;
            break;
        }
    }
    fclose(fin);
    fclose(fout);
    return NULL;
}

int
main(int argc, char *argv[])
{
    char *end;
    int fd12[2];
    int fd21[2];
    pipe(fd12);
    pipe(fd21);
    FILE *f = fdopen(fd12[1], "w");
    fprintf(f, "1\n");
    fflush(f);
    int stop = strtol(argv[1], &end, BASE);
    if (!fork()) {
        close(fd21[1]);
        close(fd12[0]);
        FILE *fin = fdopen(fd21[0], "r");
        FILE *fout = fdopen(fd12[1], "w");
        no_code_duplicate(fin, fout, stop, 2);
        exit(EXIT_SUCCESS);
    }
    if (!fork()) {
        close(fd12[1]);
        close(fd21[0]);
        FILE *fin = fdopen(fd12[0], "r");
        FILE *fout = fdopen(fd21[1], "w");
        no_code_duplicate(fin, fout, stop, 1);
        exit(EXIT_SUCCESS);
    }
    close(fd21[0]);
    close(fd12[0]);
    close(fd12[1]);
    close(fd21[1]);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    fclose(f);
    return 0;
}
