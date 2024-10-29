#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum
{
    ERROR_STAT = -1,
    MIN_ARGC = 2
};

int
arePathsLinked(const char *file1, const char *file2)
{
    struct stat file1_stat, file2_stat;
    if ((stat(file1, &file1_stat) == ERROR_STAT) || (stat(file2, &file2_stat) == ERROR_STAT)) {
        perror("Stat error");
        exit(EXIT_FAILURE);
    }
    if (file1_stat.st_ino == file2_stat.st_ino && file1_stat.st_dev == file2_stat.st_dev) {
        return 1;
    }
    return 0;
}

int
compareStrings(const void *a, const void *b)
{
    return strcmp(*(const char ) a, *(const char ) b);
}

int
main(int argc, char *argv[])
{
    printf("%d\n", argc);
    if (argc < MIN_ARGC) {
        return EXIT_SUCCESS;
    }
    char uniquePaths = (char ) malloc(argc * sizeof(char *));
    if (!uniquePaths) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    int uniquePathsCount = 0;
    for (int i = 1; i < argc; i++) {
        if ((!access(argv[i], F_OK)) != 1) {
            continue;
        }
        int isUnique = 1;
        for (int j = 0; j < uniquePathsCount; j++) {
            if (arePathsLinked(argv[i], uniquePaths[j])) {
                if (strcmp(argv[i], uniquePaths[j]) > 0) {
                    free(uniquePaths[j]);
                    if (!(uniquePaths[j] = strdup(argv[i]))) {
                        perror("Memory allocation error");
                        exit(EXIT_FAILURE);
                    }
                }
                isUnique = 0;
                break;
            }
        }
        if (isUnique) {
            uniquePaths[uniquePathsCount] = strdup(argv[i]);
            if (!uniquePaths[uniquePathsCount]) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            uniquePathsCount++;
        }
    }
    qsort(uniquePaths, uniquePathsCount, sizeof(*uniquePaths), compareStrings);
    for (int i = 0; i < uniquePathsCount; i++) {
        printf("%s\n", uniquePaths[i]);
        free(uniquePaths[i]);
    }
    free(uniquePaths);
    return 0;
}