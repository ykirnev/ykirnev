def divdigit(n):
    mas = [0] * 10
    for i in range(1, 10):
        if n % i == 0:
            mas[i] = 1
    n = str(n)
    cnt = 0
    for i in range(len(n)):
        if mas[int(n[i])] == 1:
            cnt += 1
    return cnt