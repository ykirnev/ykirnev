#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void
handl(int sig)
{
    signal(SIGINT, handl);
    signal(SIGQUIT, handl);
    if (sig == SIGINT) {
        flag = 0;
    } else if (sig == SIGQUIT) {
        flag = 1;
    }
}

int
main(void)
{
    int x;
    long long sum = 0;
    signal(SIGINT, handl);
    signal(SIGQUIT, handl);
    printf("%d\n", getpid());
    fflush(stdout);
    while (scanf("%d", &x) == 1) {
        if (flag == 1) {
            sum = sum * x;
        } else {
            sum = sum + x;
        }
        sum = sum & (~0u);
        printf("%d\n", (int) sum);
        fflush(stdout);
    }
    return 0;
}
