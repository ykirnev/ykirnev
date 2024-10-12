n, k, d = map(int, input().split())
cur_mod = n % k
n = str(n)
for i in range(d):
    cur_mod = 10 * cur_mod + 9
    dl = cur_mod % k
    if dl >= 10:
        print(-1)
        break
    else:
        n += str(9 - dl)
    cur_mod = 0
else:
    print(n)


