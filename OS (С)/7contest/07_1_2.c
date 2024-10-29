#include <stdio.h>
#include <string.h>
#include <limits.h>

enum
{
    MAX_ANSWER_SIZE = 21,
    SYSTEM_BASE = 3,
    PREV_LLONG_MIN_VALUE = -3074457345618258603
};

int
main()
{
    char input;
    long long answer;
    int zero_flag;
    int print_flag;
    int change_flag;
    char max_answer[MAX_ANSWER_SIZE] = "18446744073709551616";
    input = getchar();
    while (input != EOF) {
        answer = 0;
        zero_flag = 1;
        print_flag = 0;
        change_flag = 0;
        while (input == 'a' || input == '0' || input == '1') {
            if (print_flag == 1) {
                input = getchar();
                continue;
            }
            if (zero_flag == 1) {
                if (input == '0') {
                    change_flag = 1;
                    input = getchar();
                    continue;
                } else {
                    zero_flag = 0;
                }
            }
            if ((answer >= LLONG_MAX / SYSTEM_BASE + 1)) {
                printf("%s\n", max_answer);
                print_flag = 1;
                continue;
            }
            if ((answer < LLONG_MIN / SYSTEM_BASE - 1)) {
                printf("%s\n", max_answer);
                print_flag = 1;
                continue;
            }
            if (answer == PREV_LLONG_MIN_VALUE) {
                if (input == '1')  {
                    printf("%lld\n", LLONG_MIN);
                } else {
                    printf("%s\n", max_answer);
                }
                print_flag = 1;
                continue;
            }
            if (input == '1') {
                answer = answer * 3 + 1;
                change_flag = 1;
            } else if (input == 'a') {
                answer = answer * 3 - 1;
                change_flag = 1;
            } else {
                answer = answer * 3;
                change_flag = 1;
            }
            input = getchar();
        }
        if ((print_flag != 1) && (change_flag == 1)) {
            printf("%lld\n", answer);
        }
        input = getchar();
    }
    return 0;
}
