def dist(l, k_x, k_v, a_x, a_v):
    x_dif = (a_x - k_x + l) % l
    v_dif = k_v - a_v
    if x_dif == 0:
        return 0
    else:
        res = 10 ** 100
    if v_dif < 0:
        x_dif = (-x_dif + l) % l
        v_dif *= -1
    if v_dif != 0:
        res = min(res, x_dif / v_dif)
    return res


l, k_x, k_v, a_x, a_v = map(float, input().split())
answer = min(dist(l, k_x, k_v, a_x, a_v), dist(l, k_x, k_v, (-a_x + l) % l, -a_v))
if answer == 10**100:
    print('No')
else:
    print('Yes')
    print(f"{answer:.10f}")