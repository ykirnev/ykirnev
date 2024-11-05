n, c = map(int, input().split())
s = input()
max_len = 0
left = 0
cnt_a = 0
cnt_b = 0
if c == 0:
    flag = 0
    for right in range(n):
        if s[right] == 'a':
            cnt_a += 1
        elif s[right] == 'b' and cnt_a > 0:
            flag = 1
        while cnt_a > 0 and flag:
            if s[left] == 'a':
                cnt_a -= 1
            left += 1
            if cnt_a == 0:
                flag = 0
        max_len = max(max_len, right - left + 1)
else:
    rudeness = 0
    for right in range(n):
        if s[right] == 'a':
            cnt_a += 1
        elif s[right] == 'b':
            rudeness += cnt_a
            cnt_b += 1
        while rudeness > c:
            if s[left] == 'a':
                cnt_a -= 1
                rudeness -= cnt_b
            elif s[left] == 'b':
                cnt_b -= 1
            left += 1
        if (cnt_a == 0 or cnt_b == 0) or rudeness <= c:
            max_len = max(max_len, right - left + 1)
print(max_len)