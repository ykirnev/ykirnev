import sys

def find_path(node, p):
    path = []
    while node in p:
        path.append(node)
        node = p[node]
    path.append(node)
    return path


def find_lca(node1, node2, p):
    path1 = find_path(node1, p)
    path2 = find_path(node2, p)
    path2_set = set(path2)
    for ancestor in path1:
        if ancestor in path2_set:
            return ancestor
    return None


n = int(input())
p = {}
for _ in range(n - 1):
    c, par = input().split()
    p[c] = par
people = set(p.keys()).union(set(p.values()))
root = (people - set(p.keys())).pop()

query = sys.stdin.readline().strip()
while query:
    if not query:
        break
    node1, node2 = query.split()
    lca = find_lca(node1, node2, p)
    print(lca)
    query = sys.stdin.readline().strip()
