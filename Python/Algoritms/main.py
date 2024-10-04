def pisano_period(m):
    a, b = 0, 1
    for i in range(0, m * m):
        a, b = b, (a + b) % m
        if (a == 0 and b == 1):
            return i + 1

def fib_mod(n, m):
    pisano = pisano_period(m)
    n = n % pisano

    if n <= 1:
        return n

    a, b = 0, 1
    for _ in range(n - 1):
        a, b = b, (a + b) % m

    return b

def main():
    n, m = map(int, input().split())
    print(fib_mod(n, m))

if __name__ == "__main__":
    main()
