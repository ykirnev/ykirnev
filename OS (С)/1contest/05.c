#include <stdio.h>
#include <stdlib.h>

void
func(int len, int tmp_len, char *mas, char *used)
{
    char c;
    if (len == tmp_len) {
        printf("%s\n", mas);
    }
    for (int i = 1; i <= len; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            c = '0' + i;
            mas[tmp_len] = c;
            func(len, tmp_len + 1, mas, used);
            used[i] = 0;
        }
    }
}

int
main(void)
{
    int len;
    char *mas;
    char *used;
    int ret_scanf;
    ret_scanf = scanf("%d", &len);
    if (ret_scanf != 1) {
        return 1;
    }
    if ((len > 9) || (len < 0)) {
        return 1;
    }
    mas = calloc((len + 1), sizeof(mas[0]));
    used = calloc((len + 1), sizeof(mas[0]));
    for (int i = 0; i <= len; i++) {
        mas[i] = '\0';
        used[i] = '\0';
    }
    func(len, 0, mas, used);
    free(mas);
    free(used);
}
