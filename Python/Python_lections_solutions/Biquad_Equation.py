a, b, c = eval(input())
if (a == b == c == 0):
    print(-1)
elif (a == b == 0 and c != 0):
    print(0)
elif (a == 0):
    if (b * c > 0):
        print(0)
    else:
        x = (-c / b) ** 0.5
        print(-x, x)
elif (c == 0):
    if (a * b > 0):
        print(0)
    else:
        x = (-b/a) ** 0.5
        print(*sorted((-x, 0, x)))
else:
    d = b * b - 4 * a * c
    if d < 0:
        print(0)
    elif d == 0:
        x = -b / (2 * a)
        y = 0
    else:
        x = (-b + d ** 0.5) / (2 * a)
        y = (-b - d ** 0.5) / (2 * a)
    if x > 0:
        if y > 0:
            print(*sorted((x**0.5, -x**0.5, y**0.5, -y**0.5)))
        else:
            print(*sorted((x**0.5, -x**0.5)))
    elif y > 0:
        print(*sorted((y ** 0.5, -y ** 0.5)))
    else:
        print(0)