def fib_digit(n):
    a = [0, 1]
    i = 1
    while i < n:
        i += 1
        a.append((a[i - 1] + a[i -2]) % 10)
    return a[i]


def main():
    n = int(input())
    print(fib_digit(n))


if __name__ == "__main__":
    main()