#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

enum
{
    KEY = 2024
};

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }
    int nproc = atoi(argv[1]);
    int semid = semget(KEY, nproc, 0600 | IPC_CREAT);
    if (semid == -1) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nproc; ++i) {
        semctl(semid, i, SETVAL, 0);
    }
    int x;
    int new_proc_id;
    for (int i = 0; i < nproc; ++i) {
        if (!fork()) {
            while (semop(semid, (struct sembuf[]){{i, -1, 0}}, 1) >= 0) {
                setbuf(stdin, NULL);
                if (scanf("%d", &x) == EOF) {
                    semctl(semid, 0, IPC_RMID);
                    break;
                }
                f("%d %d\n", i, x);
                fflush(stdout);
                if (x > 0) {
                    new_proc_id = x % nproc;
                } else {
                    new_proc_id = (x % nproc + nproc) % nproc;
                }
                semop(semid, (struct sembuf[]){{new_proc_id, 1, 0}}, 1);
            }
            exit(EXIT_SUCCESS);
        }
    }
    semop(semid, (struct sembuf[]){{0, 1, 0}}, 1);
    while (wait(NULL) >= 0)
        ;
    return 0;
}
