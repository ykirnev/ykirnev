G = [0]*5
G[1] = [2]
G[2] = [1, 3, 4, 5]
G[3] = [1, 5]
G[4] = [1, 5]
G[5] = [2]
dist = [10000000] * 5
dist[1] = 0
made = [0] * 5
d = 0
tmp = 1
while d < 1000000:
    i = tmp
    for k in range(5):
        if dist[i] + G[i][k] < dist[k]:
            dist[k] = dist[i] + G[i][k]
    d = 10000000
    for k in range(5):
        if not made[k] and dist[k] < d:
            d = dist[k]
            tmp = k

