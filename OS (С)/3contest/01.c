#include <stdio.h>

STYPE
bit_reverse(STYPE value)
{
    UTYPE while_end = -1;
    UTYPE result = 0;
    while (while_end != 0) {
        result = (result << 1) | (value & 1);
        value = value >> 1;
        while_end = while_end >> 1;
    }
    return (STYPE) result;
}
