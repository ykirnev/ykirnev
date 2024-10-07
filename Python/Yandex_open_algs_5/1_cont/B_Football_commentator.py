a, b = map(int, input().split(':'))
c, d = map(int, input().split(':'))
id = int(input())
delta = b + d - a - c
if delta < 0:
    delta = 0
elif id == 1:
    if b >= (delta + c):
        delta += 1
elif id == 2:
    if a <= d:
        delta += 1
print(delta)

