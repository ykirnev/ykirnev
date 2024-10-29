x1, y1, x2, y2, x, y = (int(input()) for _ in range(6))
if x <= x1:
    if y <= y1:
        print("SW")
    elif y < y2:
        print("W")
    else:
        print("NW")
elif x < x2:
    if y < y1:
        print("S")
    else:
        print("N")
else:
    if y <= y1:
        print("SE")
    elif y < y2:
        print("E")
    else:
        print("NE")
