def cnt_h(person):
    if person in h:
        return h[person]
    if person not in parents:
        h[person] = 0
    else:
        h[person] = cnt_h(parents[person]) + 1
    return h[person]

n = int(input())
mas = [input().split() for _ in range(n - 1)]
parents = {}
people = set()
for c, p in mas:
    parents[c] = p
    people.add(c)
    people.add(p)

root = list(people - set(parents.keys()))[0]
h = {}
for p in people:
    cnt_h(p)

for p in sorted(people):
    print(p, h[p])

