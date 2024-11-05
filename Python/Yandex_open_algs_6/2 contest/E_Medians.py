
n = int(input())
a = list(map(int, input().split()))
a = sorted(a)
left = n // 2 - 1
right = n // 2
flag = n % 2
cnt = 0
while left >= 0 or right < n:
    if left < 0:
        print(a[right], end = ' ')
        right += 1
    elif right == n:
        print(a[left], end = ' ')
        left -= 1
    elif flag:
        if left == (n - cnt) // 2:
            print(a[left], end = ' ')
            left -= 1
        else:
            print(a[right], end = ' ')
            right += 1
    else:
        print(min(a[left], a[right]), end=' ')
        if a[left] < a[right]:
            left -= 1
        else:
            right += 1
    flag = not flag
    cnt += 1
