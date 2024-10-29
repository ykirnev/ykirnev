#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t cnt = 0;
volatile sig_atomic_t tmp = 0;

void
handl(int sig)
{
    if (sig == SIGTERM) {
        exit(0);
    }
    if (cnt == 3) {
        exit(0);
    }
    printf("%d\n", tmp);
    fflush(stdout);
    cnt++;
}

int main(void){
    sigaction(SIGTERM, &(struct sigaction){.sa_handler = handl, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGINT, &(struct sigaction){.sa_handler = handl, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int low, high;
    int prime_flag = 1;
    scanf("%d %d", &low, &high);
    int i = low - 1;
    while (i < high) {
        i++;
        int j = 2;
        while (j * j <= i) {
            if (i % j == 0) {
                prime_flag = 0;
                break;
            }
            j++;
        }
        if (prime_flag == 0) {
            prime_flag = 1;
            continue;
        }
        prime_flag = 1;
        tmp = i;
    }
    printf("-1\n");
    fflush(stdout);
    exit(0);

}