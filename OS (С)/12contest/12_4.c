#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

enum
{
    MIN_NUM = 10000,
    MAX_NUM = 99999,
    SIZE_NAME = 15
};

int
main(int argc, char *argv[])
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec * 1000 + tv.tv_usec / 1000);
    char py_filename[SIZE_NAME];
    char bash_filename[SIZE_NAME];
    int rand_num = rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
    int py_snprintf_result = snprintf(py_filename, sizeof(py_filename), "file_%d.py", rand_num);
    if (py_snprintf_result < 0 || py_snprintf_result >= sizeof(py_filename)) {
        return EXIT_FAILURE;
    }
    int bash_snprintf_result = snprintf(bash_filename, sizeof(bash_filename), "bash_%d.sh", rand_num);
    if (bash_snprintf_result < 0 || bash_snprintf_result >= sizeof(bash_filename)) {
        return EXIT_FAILURE;
    }
    FILE *py_file = fopen(py_filename, "w");
    if (py_file == NULL) {
        return EXIT_FAILURE;
    }
    if (fprintf(py_file, "import sys\n") < 0 || fprintf(py_file, "result = 1\n") < 0 ||
        fprintf(py_file, "for arg in sys.argv[1:]:\n") < 0 || fprintf(py_file, "    result *= int(arg)\n") < 0 ||
        fprintf(py_file, "print(result)\n") < 0) {
        fclose(py_file);
        return EXIT_FAILURE;
    }
    fclose(py_file);
    FILE *bash_file = fopen(bash_filename, "w");
    if (bash_file == NULL) {
        return EXIT_FAILURE;
    }
    if (fprintf(bash_file, "#!/bin/bash\n") < 0 || fprintf(bash_file, "python3 %s \"$@\"\n", py_filename) < 0 ||
        fprintf(bash_file, "rm %s\n", py_filename) < 0 || fprintf(bash_file, "rm %s\n", bash_filename) < 0) {
        fclose(bash_file);
        return EXIT_FAILURE;
    }
    fclose(bash_file);
    char *mas[argc + 2];
    mas[0] = "bash";
    mas[1] = bash_filename;
    for (int i = 2; i <= argc; i++) {
        mas[i] = argv[i - 1];
    }
    mas[argc + 1] = NULL;
    execvp("bash", mas);
    return EXIT_FAILURE;
}
