import sys
sys.setrecursionlimit(100000)


def cnt_h(person):
    if person not in childrens:
        h[person] = 0
        return 0
    sm = 0
    for c in childrens[person]:
        sm += 1 + cnt_h(c)
    h[person] = sm
    return sm

n = int(input())
mas = [input().split() for _ in range(n - 1)]
childrens = {}
people = set()
for c, p in mas:
    if p not in childrens:
        childrens[p] = []
    childrens[p].append(c)
    people.add(c)
    people.add(p)

root = list(people - set(c for c, _ in mas))[0]
h = {}
cnt_h(root)
for p in sorted(people):
    print(p, h.get(p, 0))

