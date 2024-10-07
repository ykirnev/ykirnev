mas = []
for i in range(8):
    a = list(input())
    mas.append(a)
for i in range(8):
    for j in range(8):
        if mas[i][j] == 'R':
            mas[i][j] = '_'
            x = i
            y = j
            while x < 8 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                x += 1
            x = i
            while x >= 0 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                x -= 1
            x = i
            while y < 8 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                y += 1
            y = j
            while y >= 0 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                y -= 1
            mas[i][j] = 'R'
        if mas[i][j] == 'B':
            mas[i][j] = '_'
            x = i
            y = j
            while x < 8 and y < 8 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                x += 1
                y += 1
            x = i
            y = j
            while x >= 0 and y >= 0 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                x -= 1
                y -= 1
            x = i
            y = j
            while x >= 0 and y < 8 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                x -= 1
                y += 1
            x = i
            y = j
            while x < 8 and y >= 0 and (mas[x][y] != 'R' and mas[x][y] != 'B'):
                mas[x][y] = '_'
                x += 1
                y -= 1
            mas[i][j] = 'B'
cnt = 0
for i in range(8):
    for j in range(8):
        if mas[i][j] == '*':
            cnt += 1
print(cnt)