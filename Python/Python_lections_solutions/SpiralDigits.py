n, m = eval(input())
mas = [[0] * n for i in range(m)]
tmp_number = 0
x, y = 0, 0
turn_x_left, turn_y_up, turn_x_right, turn_y_down = 0, 0, 0, 0
flag = 0
type_moves = 0
while flag != m * n:
    mas[y][x] = tmp_number
    flag += 1
    if tmp_number == 9:
        tmp_number = 0
    else: tmp_number += 1
    if type_moves == 0:
        if x == n - turn_x_right - 1:
            type_moves = 1
            turn_y_up += 1
            y += 1
        else:
            x += 1
    elif type_moves == 1:
        if y == m - turn_y_down - 1:
            type_moves = 2
            turn_x_right += 1
            x -= 1
        else:
            y += 1
    elif type_moves == 2:
        if x == turn_x_left:
            type_moves = 3
            turn_y_down += 1
            y -= 1
        else:
            x -= 1
    else:
        if y == turn_y_up:
            type_moves = 0
            turn_x_left += 1
            x += 1
        else:
            y -= 1
for i in range(m):
    for j in range(n):
        print(mas[i][j], end=" ")
    print()