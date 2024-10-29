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
    int len = 0;
    for (int i = 1; i < argc; ++i) {
        len += snprintf(NULL, 0, "%s", argv[i]);
    }
    char *str = calloc(len + 1, sizeof(str[0]));
    if (str == NULL) {
        return EXIT_FAILURE;
    }
    int step = 0;
    for (int i = 1; i < argc; ++i) {
        step += snprintf(str + step, len + 1 - step, "%s", argv[i]);
    }
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec * 1000 + tv.tv_usec / 1000);
    char c_filename[SIZE_NAME];
    char bash_filename[SIZE_NAME];
    int rand_num = rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
    snprintf(c_filename, sizeof(c_filename), "file_%d.c", rand_num);
    snprintf(bash_filename, sizeof(bash_filename), "bash_%d.sh", rand_num);
    FILE *c_file = fopen(c_filename, "w");
    if (c_file == NULL) {
        free(str);
        return EXIT_FAILURE;
    }
    if (fprintf(c_file, "#include <stdio.h>\n") < 0 || fprintf(c_file, "#include <stdlib.h>\n") < 0 ||
        fprintf(c_file, "\n") < 0 || fprintf(c_file, "int\n") < 0 || fprintf(c_file, "main(void)\n") < 0 ||
        fprintf(c_file, "{\n") < 0 || fprintf(c_file, "    int i = 0;\n") < 0 ||
        fprintf(c_file, "    char summon[7] = \"summon\";\n") < 0 ||
        fprintf(c_file, "    char reject[7] = \"reject\";\n") < 0 ||
        fprintf(c_file, "    char disqualify[11] = \"disqualify\";\n") < 0 || fprintf(c_file, "    int x;\n") < 0 ||
        fprintf(c_file, "    while (scanf(\"%%d\", &x) == 1) {\n") < 0 ||
        fprintf(c_file, "        printf(\"%%s\\n\", %s);\n", str) < 0 || fprintf(c_file, "    }\n") < 0 ||
        fprintf(c_file, "    return 0;\n") < 0 || fprintf(c_file, "}\n") < 0) {
        fclose(c_file);
        free(str);
        return EXIT_FAILURE;
    }
    fclose(c_file);
    FILE *bash_file = fopen(bash_filename, "w");
    if (bash_file == NULL) {
        free(str);
        return EXIT_FAILURE;
    }
    if (fprintf(bash_file, "#!/bin/bash\n") < 0 || fprintf(bash_file, "gcc %s -o %d.exe\n", c_filename, rand_num) < 0 ||
        fprintf(bash_file, "./%d.exe\n", rand_num) < 0 || fprintf(bash_file, "rm %s\n", c_filename) < 0 ||
        fprintf(bash_file, "rm %d.exe\n", rand_num) < 0 || fprintf(bash_file, "rm %s\n", bash_filename) < 0) {
        fclose(bash_file);
        free(str);
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
    free(str);
    return EXIT_FAILURE;
}
