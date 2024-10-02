n = int(input())
tmp_len = 1
max_len = 1
while n != 0:
    prev = n
    n = int(input())
    if (n - prev) >= 0:
        tmp_len += 1
    else:
        if tmp_len > max_len:
            max_len = tmp_len
        tmp_len = 1
print(max_len)