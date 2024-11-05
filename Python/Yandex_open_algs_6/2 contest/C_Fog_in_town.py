n, k = map(int, input().split())
a = list(map(int, input().split()))
ln = len(a)
r = 0
cnt = 0
for l in range(ln):
    while r < ln and a[r] - a[l] <= k:
        r += 1
    cnt += ln - r
print(cnt)
