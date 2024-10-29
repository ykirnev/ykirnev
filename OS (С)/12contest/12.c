#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

enum
{
    NAME_SIZE = 6,
    ALPHABET_SIZE = 26
};

int
main(int argc, char *argv[])
{
    char *temp_dir;
    char temp_file[PATH_MAX];
    char bash_path[PATH_MAX];
    temp_dir = getenv("XDG_RUNTIME_DIR");
    if (!temp_dir) {
        temp_dir = getenv("TMPDIR");
    }
    if (!temp_dir) {
        temp_dir = "/tmp/";
    }
    int fd = open("/dev/urandom", O_RDONLY);
    char name[] = "random";
    unsigned long long cur;
    for (int i = 0; i < NAME_SIZE; i++) {
        read(fd, &cur, sizeof(cur));
        name[i] = 'a' + (char) (cur % ALPHABET_SIZE);
    }
    snprintf(temp_file, sizeof(temp_file), "%s%s.py", temp_dir, name);
    FILE *pyfile = fopen(temp_file, "w");
    fprintf(pyfile, "print(");
    int tmp;
    for (int i = 1; i < argc - 1; i++) {
        sscanf(argv[i], "%d", &tmp);
        fprintf(pyfile, "%d*", tmp);
    }
    sscanf(argv[argc - 1], "%d", &tmp);
    fprintf(pyfile, "%d)\n", tmp);
    fclose(pyfile);
    char bashname[] = "bashfile.sh";
    snprintf(bash_path, sizeof(bash_path), "%s%s", temp_dir, bashname);
    FILE *bashfile = fopen(bash_path, "w");
    fprintf(bashfile, "#!/bin/bash\n");
    fprintf(bashfile, "python3 %s\n", temp_file);
    fprintf(bashfile, "rm %s\n", temp_file);
    fprintf(bashfile, "rm %s%s\n", temp_dir, bashname);
    fclose(bashfile);
    chmod(bash_path, 0700);
    chmod(temp_file, 0700);
    execlp("bash", "bash", bash_path, NULL);
    _exit(1);
}
