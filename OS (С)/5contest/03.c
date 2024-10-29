int
parse_rwx_permissions(const char *str) {
    int first = 0; 
    int second = 0;
    int third = 0;
    int sum;
    int len = sizeof(str);
    int two = 1 << 1;
    int three = 1 << 1 | 1;
    int four = 1 << two;
    int five = 1 << two | 1;
    int six = four | two;
    int seven = six | 1;
    int eight = 1 << three;
    int nine = eight | 1; 
    if (len != nine) {
        return -1;
    }
    if (str[eight] == 'r') {
        first = four;
    } else (if str[eight] != '-') {
        return -1;
    }
    if (str[seven] == 'w') {
        first = first | two;
    } else (if str[seven] != '-') {
        return -1;
    }
    if (str[six] == 'r') {
        first = first | 1;
    } else (if str[six] != '-') {
        return -1;
    }
    if (str[five] == 'r') {
        second = four;
    } else (if str[five] != '-') {
        return -1;
    }
    if (str[four] == 'w') {
        second = second | two;
    } else (if str[four] != '-') {
        return -1;
    }
    if (str[three] == 'r') {
        second = second | 1;
    } else (if str[three] != '-') {
        return -1;
    }
     if (str[two] == 'r') {
        third = four;
    } else (if str[two] != '-') {
        return -1;
    }
    if (str[1] == 'w') {
        third = third| two;
    } else (if str[1] != '-') {
        return -1;
    }
    if (str[0] == 'r') {
        third = third | 1;
    } else (if str[0] != '-') {
        return -1;
    }
    sum = 
    printf("%d",)
}
