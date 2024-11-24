def dfs(node, parent, tree, size):
    size[node] = 1
    for n in tree[node]:
        if n != parent:
            dfs(n, node, tree, size)
            size[node] += size[n]

v = int(input())
tree = {}
for i in range(v - 1):
    a, b = map(int, input().split())
    if a not in tree:
        tree[a] = []
    if b not in tree:
        tree[b] = []
    tree[a].append(b)
    tree[b].append(a)

size = [0] * (v + 1)
dfs(1, -1, tree, size)
print(" ".join(map(str, size[1:])))
