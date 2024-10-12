def func(i, x, y, p):
    cnt = 0
    k = 0
    while y > i:
        if k >= x:
            return 10**10
        y -= x - k
        k = 0
        if y >= 0:
            k += p
        cnt += 1
    while y > 0:
        if x <= 0:
            return 10**10
        if y >= x:
            y -= x
        else:
            k -= x - y
            y = 0
        x -= k
        if y > 0:
            k += p
        cnt += 1
    while k > 0:
        if x <= 0:
            return 10**10
        k -= x
        if k > 0:
            x -= k
        cnt += 1
    return cnt


x = int(input())
y = int(input())
p = int(input())
res = 10**10
for i in range(0, y + 1):
    res = min(res, func(i, x, y, p))
if res == 10**10:
    print(-1)
else:
    print(res)