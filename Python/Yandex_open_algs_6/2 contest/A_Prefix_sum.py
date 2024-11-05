n = int(input())
a = list(map(int, input().split()))
pr = [0] * (n + 1)
for i in range(n):
    pr[i + 1] = pr[i] + a[i]
print(*pr[1:])
