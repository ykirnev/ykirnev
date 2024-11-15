from collections import deque


def func(n, b, ars):
    queue = deque()
    total_t = 0
    for mn in range(n):
        if ars[mn] > 0:
            queue.append((mn + 1, ars[mn]))
        served = 0
        while queue and served < b:
            entry_time, num_clients = queue.popleft()
            to_serve = min(num_clients, b - served)
            served += to_serve
            total_t += to_serve * (mn + 2 - entry_time)
            if num_clients > to_serve:
                queue.appendleft((entry_time, num_clients - to_serve))

    while queue:
        entry_time, num_clients = queue.popleft()
        total_t += num_clients * (n + 2 - entry_time)

    return total_t
n, b = map(int, input().split())
ars = list(map(int, input().split()))
print(func(n, b, ars))