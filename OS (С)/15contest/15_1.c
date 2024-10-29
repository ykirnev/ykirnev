#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int nproc = atoi(argv[1]);
    int key = atoi(argv[2]);
    int maxval = atoi(argv[3]);
    int semid = semget(key, nproc, 0600 | IPC_CREAT);
    int *reject = NULL;
    int shmid = shmget(key, 2 * sizeof(*reject), 0600 | IPC_CREAT);
    reject = shmat(shmid, NULL, 0);
    reject[0] = 0;
    reject[1] = 0;
    for (int i = 0; i < nproc; i++) {
        if (!fork()) {
            while (semop(semid, (struct sembuf[]){{i, -1, 0}}, 1) >= 0) {
                printf("%d %d %d\n", i + 1, reject[0]++, reject[1]);
                fflush(stdout);
                reject[1] = i + 1;
                if (*reject > maxval) {
                    semctl(semid, 0, IPC_RMID);
                    shmdt(reject);
                    shmctl(shmid, IPC_RMID, NULL);
                    break;
                }
                semop(semid,
                      (struct sembuf[]){{(((((*reject % nproc) * (*reject % nproc)) % nproc * (*reject % nproc)) %
                                           nproc * (*reject % nproc)) %
                                          nproc),
                                         1, 0}},
                      1);
            }
            exit(0);
        }
    }
    semop(semid, (struct sembuf[]){{0, 1, 0}}, 1);
    while (wait(NULL) >= 0)
        ;
    return 0;
}
