import math

def is_convex(points):
    def vect_proisv(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])
    n = len(points)
    pivot = min(points, key=lambda p: (p[1], p[0]))
    def polar_angle(p):
        return math.atan2(p[1] - pivot[1], p[0] - pivot[0])
    points = sorted(points, key=lambda p: (polar_angle(p), (p[0] - pivot[0])**2 + (p[1] - pivot[1])**2))
    sgn = 0
    for i in range(n):
        tmp_sgn = vect_proisv(points[i], points[(i + 1) % n], points[(i + 2) % n])
        if tmp_sgn != 0:
            if sgn == 0:
                sgn = tmp_sgn
            elif tmp_sgn * sgn < 0:
                return False
    return True
points = []
while a:=input():
    x, y = map(int, a.split(','))
    points.append((x, y))
print(is_convex(points))