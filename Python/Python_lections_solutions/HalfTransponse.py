a = list(eval(input()))
mas = []
mas.append(a)
n = len(a)
for i in range(n - 1):
    a = list(eval(input()))
    mas.append(a)
for i in range(n):
    for j in range(i + 1):
        print(mas[i][j], end='')
        if i != 0: print('', end=',')
    for j in range(i-1, -1, -1):
        print(mas[j][i], end='')
        if j != 0: print('', end=',')
    print()