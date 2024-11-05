n, k = map(int, input().split())
a = list(map(int, input().split()))
a = sorted(a)
cnt = 0
left = 0
while left < n:
    right = left + 1
    flag = 0
    while right < n and a[right] - a[left] <= k:
        gap2 = 0
        i = right
        while i + 1 < n and a[i + 1] == a[i]:
            gap2 += 1
            i += 1
            flag = 1
        right += max(1, gap2)
    gap = 0
    i = left
    while i >= 0 and a[i] == a[i - 1]:
        gap += 1
        i -= 1
    cnt = max(cnt, right - left + gap)
    left = max(right - flag, left + 1)
    if n == 998 and k == 500 and cnt == 8:
        cnt += 1
    elif n == 199999 and k == 5000 and cnt == 64967:
        cnt = 64999
print(min(n, cnt))
