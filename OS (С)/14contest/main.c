int
main(void)
{

    int pfd[2];
    pipe(pfd);
    pid_t pid1, pid2;
    if (!(pid1 = fork())) {

        dup2(pfd[1], 1);
        close(pfd[1]);
        close(pfd[0]);

        execlp("/bin/ls", "ls", "*.o", NULL);

        _exit(1);
    }
    if (!(pid2 = fork())) {

        dup2(pfd[0], 0);
        close(pfd[0]);
        close(pfd[1]);

        execlp("/usr/bin/wc", "wc", "-l", NULL);

        _exit(1);
    }
    close(pfd[0]);
    close(pfd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
