n = int(input())
a = list(map(int, input().split()))
S = sum(a)
S2 = sum(x ** 2 for x in a)
S3 = sum(x ** 3 for x in a)
ans = ((S**3 - 3 * S * S2 + 2 * S3) // 6) % 1000000007
print(ans)