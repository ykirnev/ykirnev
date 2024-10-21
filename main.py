def merge(a1, a2):
    res = []
    a1_id, a2_id = 0, 0
    a1_len, a2_len = len(a1), len(a2)
    for i in range(a1_len + a2_len):
        if a1_id < a1_len and a2_id < a2_len:
            if a1[a1_id] ** 2 % 100 < a2[a2_id] ** 2 % 100:
                res.append(a1[a1_id])
                a1_id += 1
            else:
                res.append(a2[a2_id])
                a2_id += 1
        elif a1_id == a1_len:
            res.append(a2[a2_id])
            a2_id += 1
        else:
            res.append(a1[a1_id])
            a1_id += 1
    return res


def merge_sort(a):
    if (len(a) == 1):
        return a
    mid = len(a) // 2
    left_part = merge_sort(a[:mid])
    right_part = merge_sort(a[mid:])
    return merge(left_part, right_part)


def insertion_sort(mas):
    for i in range(1, len(mas)):
        tmp = mas[i]
        j = i - 1
        while j >= 0 and tmp < mas[j]:
            mas[j + 1] = mas[j]
            j -= 1
            mas[j + 1] = tmp
    return mas


def selection_sort(mas):
    for i in range(len(mas)):
        min_id = i
        for j in range(i + 1, len(mas)):
            if mas[j] < mas[min_id]:
                min_id = j
        mas[i], mas[min_id] = mas[min_id], mas[i]
    return mas


a = [1, 3, 4, 5, 9, 10]
# a = list(eval(input()))
n = len(a)
# print(selection_sort(a))
# print(insertion_sort(a))
# print(merge_sort(a))

for i in range(n):
    for j in range(1, n - i):
        if a[j] ** 2 % 100 > a[j - 1] ** 2 % 100:
            cp = a[j]
            a[j] = a[j - 1]
            a[j - 1] = cp

sorted(a)

troom, tcond = 1, 2#map(int, input().split())
mode = 'heat'#input()
if mode == 'freeze':
    if troom > tcond:
        print(tcond)
    else:
        print(troom)
elif mode == 'heat':
    if troom < tcond:
        print(tcond)
    else:
        print(troom)
elif mode == 'auto':
    print(tcond)
elif mode == 'fan':
    print(troom)

p, v = map(int, input().split())
q, m = map(int, input().split())
if q < p:
    p, v, q, m = q, m, p, v
if (p + v) < (q - m):
    print(2 * (v + m + 1))
else:
    print(max(q + m, p + v) - min(q - m, p - v) + 1)

a = int(input())
b = int(input())
c = int(input())
if c < 0:
    print('NO SOLUTION')
elif a == 0:
    if b == c * c:
        print('MANY SOLUTIONS')
    else:
        print('NO SOLUTION')
else:
    x = c * c - b
    if x % a == 0:
        print(x // a)
    else:
        print('NO SOLUTION')