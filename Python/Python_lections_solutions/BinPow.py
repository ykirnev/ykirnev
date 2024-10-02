def BinPow(a, n, f):
    if n == 1:
        return a
    if n % 2 == 0:
        return BinPow(f(a, a), n // 2, f)
    return f(a, BinPow(a, n - 1, f))