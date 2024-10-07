#Pisano_period
def fib_mod(n, m):
    a = 0
    b = 1
    i = 0
    while True:
        cp = b
        b = (a + b) % m
        a = cp
        i = i + 1
        if a == 0 and b == 1:
            n = n % i
            break
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