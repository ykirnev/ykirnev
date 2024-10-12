def squares(w, h, *args):
    mas = [['.'] * w for i in range(h)]
    for i in range(len(args)):
        x, y, s, c = map(str, args[i])
        x, y, s = int(x), int(y), int(s)
        for j in range(s):
            for k in range(s):
                mas[y + j][x + k] = c
    for i in range(h):
        for j in range(w):
            print(mas[i][j], end ='')
        print()
a = eval(input())