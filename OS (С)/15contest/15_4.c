#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

struct message_buf
{
    long long mtype;
    long long x1;
    long long x2;
};

void
func(int proc_id, int my_queue, int n, long long maxval)
{
    struct message_buf msg;
    fflush(stdout);
    while (msgrcv(my_queue, &msg, sizeof(struct message_buf) - sizeof(long), proc_id + 1, 0) != -1) {
        long long x3 = msg.x1 + msg.x2;
        printf("%d %lld\n", proc_id, x3);
        fflush(stdout);
        if (x3 > maxval) {
            msgctl(my_queue, IPC_RMID, NULL);
            _exit(EXIT_SUCCESS);
        }
        struct message_buf next_msg = {.mtype = x3 % n + 1, .x1 = msg.x2, .x2 = x3};
        if (msgsnd(my_queue, &next_msg, sizeof(struct message_buf) - sizeof(long), 0) == -1) {
            msgctl(my_queue, IPC_RMID, NULL);
            _exit(EXIT_FAILURE);
        }
    }
}

int
main(int argc, char *argv[])
{
    if (argc != 6) {
        exit(EXIT_FAILURE);
    }
    key_t key = atoi(argv[1]);
    int n = atoi(argv[2]);
    long long value1 = atoi(argv[3]);
    long long value2 = atoi(argv[4]);
    long long maxval = atoi(argv[5]);
    int my_queue = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
    if (my_queue == -1) {
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    for (int i = 0; i < n; ++i) {
        if ((pid = fork()) == -1) {
            msgctl(my_queue, IPC_RMID, NULL);
            while (wait(NULL) >= 0)
                ;
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            func(i, my_queue, n, maxval);
        }
    }
    struct message_buf start_msg = {.mtype = 1, .x1 = value1, .x2 = value2};
    if (msgsnd(my_queue, &start_msg, sizeof(struct message_buf) - sizeof(long), 0) == -1) {
        while (wait(NULL) >= 0)
            ;
        msgctl(my_queue, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
    return 0;
}
