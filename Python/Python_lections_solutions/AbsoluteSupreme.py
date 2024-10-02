import time
mas = []
while a := input():
    mas.append(list(eval(a)))
while mas:
    mx_id = -1
    for i in range(len(mas)):
        flag = 1
        for j in range(len(mas)):
            if i != j:
                a = sorted(mas[i])
                b = sorted(mas[j])
                if (a[0] <= b[0] and a[1] <= b[1] and a[2] <= b[2] and (a[0] != b[0] or a[1] != b[1] or a[2] != b[2])):
                    flag = 0
                    break
                #if ((mas[i][0] <= mas[j][0] and mas[i][1] <= mas[j][1] and mas[i][2] <= mas[j][2] and (mas[i][0] != mas[j][0] or mas[i][1] != mas[j][1] or mas[i][2] != mas[j][2])) or (mas[i][0] <= mas[j][0] and mas[i][1] <= mas[j][2] and mas[i][2] <= mas[j][1] and (mas[i][0] != mas[j][0] or mas[i][1] != mas[j][2] or mas[i][2] != mas[j][1])) or (mas[i][0] <= mas[j][1] and mas[i][1] <= mas[j][0] and mas[i][2] <= mas[j][2] and (mas[i][0] != mas[j][1] or mas[i][1] != mas[j][0] or mas[i][2] != mas[j][2])) or (mas[i][0] <= mas[j][1] and mas[i][1] <= mas[j][2] and mas[i][2] <= mas[j][0] and (mas[i][0] != mas[j][1] or mas[i][1] != mas[j][2] or mas[i][2] != mas[j][0])) or (mas[i][0] <= mas[j][2] and mas[i][1] <= mas[j][0] and mas[i][2] <= mas[j][1] and (mas[i][0] != mas[j][2] or mas[i][1] != mas[j][0] or mas[i][2] != mas[j][1])) or (mas[i][0] <= mas[j][2] and mas[i][1] <= mas[j][1] and mas[i][2] <= mas[j][0]) and (mas[i][0] != mas[j][2] or mas[i][1] != mas[j][1] or mas[i][2] != mas[j][0])):
                 #   flag = 0
                  #  break
        if flag:
            mx_id = i
            break
    if mx_id != -1:
        print(*mas[mx_id], sep=', ')
        mas.pop(mx_id)