#include <time.h>
#include <stdio.h>
#include <string.h>

enum
{
    START_YEAR = 1900,
    START_HOUR = 12,
    TUE_WDAY = 4,
    INCORRECT_TUE_DAY = 3,
    CORRECT_TUE_WEEK = 2
};

int
main(int argc, char *argv[])
{
    int year;
    int num_ch_flag = 0;
    int prev_month = 0;
    scanf("%d", &year);
    struct tm t;
    memset(&t, 0, sizeof(t));
    year = year - START_YEAR;
    t.tm_year = year;
    t.tm_hour = START_HOUR;
    t.tm_isdst = -1;
    t.tm_mday = 1;
    mktime(&t);
    prev_month = t.tm_mon;
    while (t.tm_year == year) {
        if (prev_month != t.tm_mon) {
            num_ch_flag = 0;
            prev_month = t.tm_mon;
        }
        if (t.tm_wday == TUE_WDAY) {
            num_ch_flag++;
            if (num_ch_flag % CORRECT_TUE_WEEK == 0) {
                if (t.tm_mday % INCORRECT_TUE_DAY != 0) {
                    printf("%d %d\n", t.tm_mon + 1, t.tm_mday);
                }
            }
        }
        t.tm_mday++;
        mktime(&t);
    }
    return 0;
}
