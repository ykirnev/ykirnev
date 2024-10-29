#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/fcntl.h>

enum
{
    MIN_NUM = 10000,
    MAX_NUM = 99999,
    SIZE_NAME = 15,
    RAND_NUM_LEN = 6,
    NUMBER_LETTERS = 52
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
    int no_srand = open("/dev/urandom", O_RDONLY);
    char buf;
    char no_srand_value[RAND_NUM_LEN];
    for (int i = 0; i < RAND_NUM_LEN; i++) {
        read(no_srand, &buf, sizeof(buf));
        no_srand_value[i] = 'a' + (char) (buf % NUMBER_LETTERS);
    }
    char c_filename[SIZE_NAME];
    char bash_filename[SIZE_NAME];
    snprintf(c_filename, sizeof(c_filename), "file_%s.c", no_srand_value);
    snprintf(bash_filename, sizeof(bash_filename), "bash_%s.sh", no_srand_value);
    FILE *c_file = fopen(c_filename, "w");
    if (c_file == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(c_file, "#include <stdio.h>\n");
    fprintf(c_file, "#include <stdlib.h>\n");
    fprintf(c_file, "\n");
    fprintf(c_file, "int\n");
    fprintf(c_file, "main(void)\n");
    fprintf(c_file, "{\n");
    fprintf(c_file, "    int i = 0;\n");
    fprintf(c_file, "    char summon[7] = \"summon\";\n");
    fprintf(c_file, "    char reject[7] = \"reject\";\n");
    fprintf(c_file, "    char disqualify[11] = \"disqualify\";\n");
    fprintf(c_file, "    int x;\n");
    fprintf(c_file, "    while (scanf(\"%%d\", &x) == 1) {\n");
    fprintf(c_file, "        printf(\"%%s\\n\", %s);\n", str);
    fprintf(c_file, "    }\n");
    fprintf(c_file, "    return 0;\n");
    fprintf(c_file, "}\n");
    fclose(c_file);
    FILE *bash_file = fopen(bash_filename, "w");
    if (bash_file == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(bash_file, "#!/bin/bash\n");
    fprintf(bash_file, "gcc %s -o %s.exe\n", c_filename, no_srand_value);
    fprintf(bash_file, "./%s.exe\n", no_srand_value);
    fprintf(bash_file, "rm %s\n", c_filename);
    fprintf(bash_file, "rm %s.exe\n", no_srand_value);
    fprintf(bash_file, "rm %s\n", bash_filename);
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
