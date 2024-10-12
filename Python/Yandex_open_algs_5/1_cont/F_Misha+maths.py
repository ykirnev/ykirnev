n = int(input())
a = list(map(int, input().split()))
sum_mods = 0
id_pair = -1
id_nech = -1
second = a[0]
flag = 1
flag_2 = 1
sum_mods += second % 2
if second % 2 == 1:
    id_nech == 1
    flag_2 = 0
for i in range(1, n):
    first = second
    second = a[i]
    sum_mods = (sum_mods + (second % 2)) % 2
    if flag:
        if first % 2 == 1 and second % 2 == 1:
            flag = 0
            id_pair = i - 1
    if flag_2:
        if second % 2 == 1:
            flag_2 = 0
            id_nech = i
if sum_mods == 1:
    print('+'*(n - 1))
elif id_pair != -1:
    print('+' * id_pair + 'x' + '+' * (n - id_pair - 2))
else:
    print('+' * id_nech + 'x' + '+' * (n - id_nech - 3))
