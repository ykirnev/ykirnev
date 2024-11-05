n = int(input())
a = list(map(int, input().split()))
pr = [0] * n
suf = [0] * n
pr[0] = a[0]
for i in range(1, n):
    pr[i] = pr[i - 1] + a[i]
suf[n - 1] = a[n - 1]
for i in range(n - 2, -1, -1):
    suf[i] = suf[i + 1] + a[i]
t = sum(i * a[i] for i in range(1, n))
mn = t
for k in range(1, n):
    t = t + pr[k - 1] - suf[k]
    mn = min(mn, t)
print(mn)
