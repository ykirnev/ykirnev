n = int(input())
for i in range(2, int(n**0.5)+1):
    x = i ** 2
    while x <= n:
        if x == n:
            print("YES")
            exit()
        x = x * i
print("NO")