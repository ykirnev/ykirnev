from collections import deque, defaultdict

n = int(input())
a, b = map(int, input().split())

pr = {a: 1, b: 2}
if abs(a - b) == 2:
    pr[a] = 1
    pr[b] = 1
    pr[(a % 4) + 1] = 3
    pr[(b % 4) + 1] = 3
else:
    if (a % 4) + 1 == b:
        pr[a] = 1
        pr[b] = 2
        pr[(b % 4) + 1] = 3
        pr[((b + 1) % 4) + 1] = 4
    else:
        pr[b] = 1
        pr[a] = 2
        pr[(a % 4) + 1] = 3
        pr[((a + 1) % 4) + 1] = 4

queues = defaultdict(deque)
r_times = {}

r = []
for i in range(n):
    d, t = map(int, input().split())
    r.append((t, d, i))
r.sort()
queues = defaultdict(deque)
for t, d, i in r:
    queues[d].append((t, i))

cur_time = 0

while r:
    r.sort()
    tmp = set()
    hi_pr = 4
    last_time = -1
    cur_time += 1
    for pri in sorted(pr, key=lambda x: pr[x]):
        if not queues[pri]:
            continue
        t, idx = queues[pri][0]
        if t <= cur_time:
            if pr[pri] <= hi_pr:
                r_times[idx] = cur_time
                queues[pri].popleft()
                tmp.add(idx)
                hi_pr = min(pr[pri], hi_pr)
                last_time = t
            else:
                break
    if not tmp:
        next = [t for t, dir, idx in r if idx not in tmp]
    else:
        r = [(t, d, i) for t, d, i in r if i not in tmp]

for i in range(n):
    print(r_times[i])
