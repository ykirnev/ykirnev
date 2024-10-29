#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    if (fork()) {
        wait(NULL);
        printf("1\n");
    } else {
        if (!fork()) {
            printf("3 ");
        } else {
            wait(NULL);
            printf("2 ");
        }
    }
    return 0;
}