def gcdmy(a, b):
    if a == 0 or b == 0:
        return a + b
    if a > b:
        return gcdmy(a % b, b)
    return gcdmy(b % a, a)


a = 2#int(input())
b = 5#int(input())
print(gcdmy(a, b))

if (b > a):
    a, b = b, a
while b != 0:
    a, b = b, a % b
print(a)

def is_palindrome(string):
    if len(string) == 1:
        return 1
    if string[::-1]==string:
        return len(string)
    return is_palindrome(string[:-1:])

print(is_palindrome('qwqwqwqwq'))

a = [1, 4, 2, 4, 6, 7]
#a = eval(input())
mx = max(a[0], a[1])
mx2 = a[0] + a[1] - mx
for i in range(2, len(a)):
    new = a[i]
    if new > mx:
        mx2 = mx
        mx = new
    elif new > mx2:
        mx2 = new

print(mx, mx2)

mas = [1, 1]
n = 10 #int(input())
for i in range(2, n):
    new = mas[i - 1] + mas[i - 2]
    mas.append(new)
print(mas[-1])
print(*mas)

def merge(a1, a2):
    res = []
    a1_id, a2_id = 0, 0
    a1_len, a2_len = len(a1), len(a2)
    for i in range(a1_len + a2_len):
        if a1_id < a1_len and a2_id < a2_len:
            if a1[a1_id] < a2[a2_id]:
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
#a = [1, 3, 4, 5, 9, 10]
a = list(eval(input()))
n = len(a)
print(merge_sort(a))

for i in range(n):
    for j in range(1, n - i):
        if a[j] > a[j - 1]:
            cp = a[j]
            a[j] = a[j - 1]
            a[j - 1] = cp

sorted(a)




