n, k = map(int, input().split())
a = list(map(int, input().split()))
a = sorted(a)
left = 0
cnt = 0
while left < n:
    gap = 0
    gap2 = 0
    right = left + cnt
    while right < n and a[right] - a[left] <= k:
        if a[left] == a[right]:
            gap2 += 1
        if a[right] == a[right - 1]:
            gap += 1
        else:
            gap = 0
        right += 1
    cnt = max(cnt, right - left)
    left += max(gap2, 1)
print(cnt)
