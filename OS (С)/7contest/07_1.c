#include <stdio.h>
#include <string.h>
#include <limits.h>

enum
{
    MAX_ANSWER_SIZE = 21,
    SYSTEM_BASE = 3
};

void
func(char *str)
{
    long long answer = 0;
    int len = strlen(str);
    long long tmp_degree_three = 1;
    int counter = 0;
    char max_answer[MAX_ANSWER_SIZE] = "18446744073709551616";
    for (int i = len - 1; i >= 0; i--) {
        counter++;
        if (counter == 42) {
            for(int j = 0; j <= i; j++) {
                if (str[j] != '0') {
                    printf("%s\n", max_answer);
                    return;
                }
            }
            break;
        }
        if (str[i] == 'a') {
            if (answer > 0) {
                answer += (-1) * tmp_degree_three;
                tmp_degree_three *= SYSTEM_BASE;
                continue;
            }
            if (LLONG_MIN - (-1) * tmp_degree_three > answer) {
                printf("%s\n", max_answer);
                return;
            }
            answer += tmp_degree_three * (-1);
        } else if (str[i] == '1') {
            if (answer < 0) {
                answer += tmp_degree_three;
                tmp_degree_three *= SYSTEM_BASE;
                continue;
            }
            if (LLONG_MAX - tmp_degree_three < answer) {
                printf("%s\n", max_answer);
                return;
            }
            answer += tmp_degree_three;
        }
        tmp_degree_three *= SYSTEM_BASE;
    }
    printf("%lld\n", answer);
    return;
}

int
main()
{
    char str[1000];
    while (scanf("%s", str) == 1) {
        func(str);
    }
    return 0;
}
