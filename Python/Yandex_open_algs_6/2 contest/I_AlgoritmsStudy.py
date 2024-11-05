n = int(input())
ints = list(map(int, input().split()))
use = list(map(int, input().split()))
moods = list(map(int, input().split()))
algs = [(i, ints[i], use[i]) for i in range(n)]
algs_int = sorted(algs, key=lambda x: (-x[1], -x[2], x[0]))
algs_use = sorted(algs, key=lambda x: (-x[2], -x[1], x[0]))
int_i = 0
use_i = 0
studied = set()
result = []
for mood in moods:
    if mood == 0:
        while int_i < n:
            id = algs_int[int_i][0]
            if id not in studied:
                result.append(id + 1)
                studied.add(id)
                int_i += 1
                break
            int_i += 1
        else:
            break
    else:
        while use_i < n:
            id = algs_use[use_i][0]
            if id not in studied:
                result.append(id + 1)
                studied.add(id)
                use_i += 1
                break
            use_i += 1
        else:
            break
print(*result)
