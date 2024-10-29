#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

enum
{
    MAX_CNT_SIG = 5
};
volatile sig_atomic_t Count = 0;

void
handl(int sig)
{
    if (sig == SIGHUP) {
        if (Count < MAX_CNT_SIG) {
            printf("%d\n", Count);
            fflush(stdout);
            Count++;
        } else {
            exit(EXIT_SUCCESS);
        }
    }
}
int
main(void)
{
    sigaction(SIGHUP, &(struct sigaction){.sa_handler = handl, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
}
