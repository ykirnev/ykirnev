flag = 0
while a := input():
    mas = a.split()
    for i in range(len(mas)):
        s = mas[i]
        if s[0] == '-' and s[1:].isdigit() or s.isdigit():
            s = int(s)
            if flag == 0:
                flag = 1
                mx = s
            else:
                mx = max(mx, s)
if flag:
    print(mx)
else:
    print(0)