from decimal import Decimal, getcontext, ROUND_HALF_UP

def bernoulli_numbers(n):
    A = [Decimal(0)] * (n+1)
    A[0] = Decimal(1)
    for m in range(1, n+1):
        A[m] = Decimal(1) / (m+1)
        for j in range(m, 0, -1):
            A[j-1] = j * (A[j-1] - A[j])
    return [A[k] for k in range(n+1)]

def pi_count(E):
    C = Decimal(426880) * Decimal(10005).sqrt()
    K = Decimal(6)
    M = Decimal(1)
    X = Decimal(1)
    L = Decimal(13591409)
    S = L
    for i in range(1, E):
        M = (K ** 3 - 16 * K) * M / Decimal(i) ** 3
        L += 545140134
        X *= -262537412640768000
        S += Decimal(M * L) / X
        K += 12
    pi = C / S
    return pi

def taylor_sin(x, E):
    term = x
    result = term
    n = 1
    while abs(term) > Decimal('1e-' + str(E + 100)):
        term *= -x * x / Decimal((2 * n) * (2 * n + 1))
        result += term
        n += 1
    return result

def taylor_cos(x, E):
    term = Decimal(1)
    result = term
    n = 1
    while abs(term) > Decimal('1e-' + str(E + 100)):
        term *= -x * x / Decimal((2 * n - 1) * (2 * n))
        result += term
        n += 1
    return result

def taylor_tan_using_sin_cos(x, E):
    sin_x = taylor_sin(x, E)
    cos_x = taylor_cos(x, E)
    return sin_x / cos_x

def func(A, E):
    getcontext().prec = E + 10
    pi = pi_count(E)
    rads = Decimal(A) * pi / Decimal(200)
    answ = taylor_tan_using_sin_cos(rads, E)
    getcontext().prec = E
    return answ

A = float(input())
E = int(input())
getcontext().prec = E
x = func(A, E)
getcontext().prec = E
print(x * Decimal(1))