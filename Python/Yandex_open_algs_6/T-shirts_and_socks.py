a, b, c, d = (int(input()) for _ in range(4))
if a == 0:
    m = 1
    n = c + 1
elif b == 0:
    m = 1
    n = d + 1
elif c == 0:
    m = a + 1
    n = 1
elif d == 0:
    m = b + 1
    n = 1
else:
    if a <= b and c <= d or a > b and c > d:
        option1_m, option1_n = min(a, b) + 1, min(c, d) + 1
    else:
        option1_m, option1_n = max(a, b) + 1, max(c, d) + 1
    option2_m, option2_n = 1, max(c, d) + 1
    option3_m, option3_n = max(a, b) + 1, 1
    m, n = min((option1_m, option1_n), (option2_m, option2_n),
               (option3_m, option3_n), key=lambda x: x[0] + x[1])
print(m, n)
