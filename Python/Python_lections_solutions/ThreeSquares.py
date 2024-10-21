import time

seq = set(eval(input()))
lim = 200000
st = time.time()
squares = {a * a + b * b + c * c for a in range(1, int((lim) ** 0.5) + 1) for b in range(a, int((lim - a * a) ** 0.5) + 1) for c in
           range(b, int((lim - a * a - b * b) ** 0.5) + 1) }
cnt = 0
for x in seq:
    if x in squares:
        cnt += 1
fin = time.time()
print(cnt)
