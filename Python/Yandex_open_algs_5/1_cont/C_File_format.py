n = int(input())
sum = 0
for i in range(n):
    a = int(input())
    sum += (a + 1) // 4 + min(4 - a % 4, a % 4)
print(sum)
