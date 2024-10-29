#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *
normalize(const char *path)
{
    char *normalized = NULL;
    if (path == NULL || path[0] == '\0') {
        return NULL;
    }
    if ((strlen(path) == 2) && (path[0] == '/') && path[1] == '.') {
        normalized = calloc(2, sizeof(char));
        normalized[0] = '/';
        normalized[1] = '\0';
        return normalized;
    }
    if ((strlen(path) == 3) && (path[0] == '/') && path[1] == '.' && path[2] == '.') {
        normalized = calloc(2, sizeof(char));
        normalized[0] = '/';
        normalized[1] = '\0';
        return normalized;
    }
    normalized = calloc(strlen(path) + 2, sizeof(char));
    int len = 0;
    for (int i = 0; path[i] != '\0'; i++) {
        if ((strlen(path) > i + 2) && (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '/')) {
            i += 1;
            continue;
        } else if ((strlen(path) > i + 2) && path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.' &&
                   (path[i + 3] == '/' || path[i + 3] == '\0')) {
            i += 2;
            if (len > 0) {
                while (len > 0 && normalized[len - 1] != '/') {
                    len = len - 1;
                }
                len = len - 1;
            }
            if (path[i] == '\0') {
                break;
            }
        } else {
            normalized[len++] = path[i];
        }
    }
    if (normalized[len - 1] != '/') {
        normalized[len++] = '/';
    }
    if ((normalized[len - 1] == '/') && (normalized[len - 2] == '.') && (normalized[len - 3] == '/')) {
        normalized[len - 2] = '\0';
        normalized[len - 1] = '\0';
    }
    normalized[len] = '\0';
    len = strlen(normalized);
    if (len > 1) {
        normalized[len - 1] = '\0';
    }
    return normalized;
}

char *
relativize_path(const char *path1, const char *path2)
{
    if ((path1 == NULL) || (path2 == NULL)) {
        return NULL;
    }
    char *normalized1 = NULL;
    normalized1 = normalize(path1);
    char *normalized2 = NULL;
    normalized2 = normalize(path2);
    int len1 = strlen(normalized1);
    int len2 = strlen(normalized2);
    char *answer = NULL;
    if ((strcmp(normalized1, "/") == 0) && (strcmp(normalized2, "/") == 0)) {
        answer = calloc(2, sizeof(normalized1[0]));
        answer[0] = '.';
        answer[1] = '\0';
        if (normalized1 != NULL) {
            free(normalized1);
        }
        if (normalized2 != NULL) {
            free(normalized2);
        }
        return answer;
    }

    if (strcmp(normalized1, "/") == 0) {
        answer = calloc(len2, sizeof(normalized1[0]));
        for (int i = 0; i < len2; i++) {
            answer[i] = normalized2[i + 1];
        }
        if (normalized1 != NULL) {
            free(normalized1);
        }
        if (normalized2 != NULL) {
            free(normalized2);
        }
        return answer;
    }
    if (strcmp(normalized2, "/") == 0) {
        answer = calloc(2 * len1, sizeof(normalized1[0]));
        int index = 0;
        int flag_slash = 0;
        for (int i = 1; i < len1; i++) {
            if (normalized1[i] == '/') {
                if (flag_slash != 0) {
                    answer[index++] = '/';
                }
                answer[index++] = '.';
                answer[index++] = '.';
                flag_slash++;
            }
        }
        if (normalized1 != NULL) {
            free(normalized1);
        }
        if (normalized2 != NULL) {
            free(normalized2);
        }
        if (flag_slash != 0) {
            return answer;
        }
        answer[0] = '.';
        answer[1] = '\0';
        return answer;
    }
    int tmp_id = 0;
    int i = 0;
    int id_last_slash = 0;
    while ((tmp_id < len1) && (tmp_id < len2) && (normalized1[tmp_id] == normalized2[tmp_id])) {
        if (normalized1[tmp_id] == '/') {
            id_last_slash = tmp_id;
        }
        tmp_id = tmp_id + 1;
    }
    if (tmp_id == len1) {
        while (tmp_id > 0) {
            tmp_id--;
            if (normalized1[tmp_id] == '/') {
                answer = calloc(len2 - len1 + 1, sizeof(char));
                for (i = 0; normalized2[tmp_id + 1 + i] != '\0'; i++) {
                    answer[i] = normalized2[tmp_id + 1 + i];
                }
                answer[i] = '\0';
                if (normalized1 != NULL) {
                    free(normalized1);
                }
                if (normalized2 != NULL) {
                    free(normalized2);
                }
                if ((strcmp(answer, "../") == 0) || (strlen(answer) < 1)) {
                    answer = calloc(2, sizeof(char));
                    answer[0] = '.';
                    answer[1] = '\0';
                    return answer;
                }
                return answer;
            }
        }
    }
    int not_both_dir = 0;
    if (strcmp(normalized2, "/") == 0) {
        not_both_dir = 1;
    }
    for (int i = tmp_id; i < len1; i++) {
        if (normalized1[i] == '/') {
            not_both_dir = not_both_dir + 1;
        }
    }
    if ((len2 - tmp_id == 0) && ((normalized1[tmp_id + 1] != '/'))) {
        not_both_dir -= 1;
    }
    int answer_len = (not_both_dir * 3) + len2 - tmp_id + 1;
    if (answer_len <= 0) {
        answer = calloc(2, sizeof(char));
        answer[0] = '.';
        answer[1] = '\0';
        if (normalized1 != NULL) {
            free(normalized1);
        }
        if (normalized2 != NULL) {
            free(normalized2);
        }
        return answer;
    }
    answer = calloc(answer_len, sizeof(char));
    answer[0] = '\0';
    for (int i = 0; i < not_both_dir; i++) {
        strcat(answer, "../");
    }
    if (tmp_id != id_last_slash + 2) {
        tmp_id = id_last_slash + 1;
    }
    int answer_tmp_id = 3 * not_both_dir;
    while (normalized2[tmp_id] != '\0') {
        answer[answer_tmp_id] = normalized2[tmp_id];
        tmp_id++;
        answer_tmp_id++;
    }
    answer[strlen(answer)] = '\0';
    if (normalized1 != NULL) {
        free(normalized1);
    }
    if (normalized2 != NULL) {
        free(normalized2);
    }
    if ((strlen(answer) < 1)) {
        answer = calloc(2, sizeof(char));
        answer[0] = '.';
        answer[1] = '\0';
        return answer;
    }
    if (strcmp(answer + strlen(answer) - 3, "../") == 0) {
        answer[strlen(answer) - 1] = '\0';
    }
    return answer;
}