mas = [[0] * 101 for i in range(101)]
while a := input():
    a,b = list(map(int, a.split(',')))
    mas[a][b] += 1
for i in range(101):
    for j in range(101):
        if (mas[i][j] != 0):
            for k in range(mas[i][j]):
                print(i, ', ', j, sep = '')
