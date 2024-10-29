#include <time.h>
#include <stdio.h>
#include <string.h>

enum
{
    FIRST_TM_YEAR = 2021,
    START_YEAR = 1900,
    FIRST_TM_MON = 4,
    FIRST_TM_MDAY = 26,
    FIRST_TM_HOUR = 11,
    FIRST_TM_MIN = 14,
    FLAG_YDAY = 256,
    DIF_DAY = 29,
    DIF_HOUR = 12,
    DIF_MIN = 44,
    FLAG_MONDAY_COUNTS = 4,
    PRINT_DAY_FLAG = 10,
    PRINT_MON_FLAG = 9
};
int
main()
{
    struct tm moon;
    memset(&moon, 0, sizeof(moon));
    moon.tm_year = FIRST_TM_YEAR - START_YEAR;
    moon.tm_mon = FIRST_TM_MON;
    moon.tm_mday = FIRST_TM_MDAY;
    moon.tm_hour = FIRST_TM_HOUR;
    moon.tm_min = FIRST_TM_MIN;
    moon.tm_isdst = -1;
    mktime(&moon);
    int year;
    int monday_flag = 0;
    scanf("%d", &year);
    if (year < FIRST_TM_YEAR) {
        while ((moon.tm_yday > FLAG_YDAY) || (moon.tm_year != year - START_YEAR)) {
            moon.tm_mday -= DIF_DAY;
            moon.tm_hour -= DIF_HOUR;
            moon.tm_min -= DIF_MIN;
            mktime(&moon);
        }
    }
    while ((moon.tm_yday < FLAG_YDAY) || (moon.tm_year != year - START_YEAR)) {
        moon.tm_mday += DIF_DAY;
        moon.tm_hour += DIF_HOUR;
        moon.tm_min += DIF_MIN;
        mktime(&moon);
    }
    while (monday_flag != FLAG_MONDAY_COUNTS) {
        moon.tm_mday++;
        mktime(&moon);
        if (moon.tm_wday == 1) {
            monday_flag++;
        }
    }
    printf("%d-", moon.tm_year + START_YEAR);
    if (moon.tm_mon < PRINT_MON_FLAG) {
        printf("0");
    }
    printf("%d-", moon.tm_mon + 1);
    if (moon.tm_mday < PRINT_DAY_FLAG) {
        printf("0");
    }
    printf("%d\n", moon.tm_mday);
    return 0;
}
