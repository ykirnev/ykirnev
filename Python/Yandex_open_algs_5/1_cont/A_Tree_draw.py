p, v = map(int, input().split())
q, m = map(int, input().split())
v = abs(v)
m = abs(m)
if q < p:
    p, v, q, m = q, m, p, v
if q - m <= p + v:
    print(max(q + m, p + v) - min(q - m, p - v) + 1)
else:
    print(2 * v + 2 * m + 2)
