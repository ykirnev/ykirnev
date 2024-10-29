#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int
func(char *cmd_name)
{
    if (fork()) {
        int status;
        wait(&status);
        if ((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        execlp(cmd_name, cmd_name, NULL);
        _exit(1);
    }
}

int
main(int argc, char **argv)
{
    int answer = (func(argv[1]) && func((argv[2]))) || func(argv[3]);
    return answer;
}
