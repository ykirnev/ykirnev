def is_prime(n = 0):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def nonprime(n = 0):
    cur = n + 1
    while True:
        if cur == 1 or not is_prime(cur):
            yield cur
        cur += 1

