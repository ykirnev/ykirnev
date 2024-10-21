txt = []
while a:=input():
    txt += a.split()
m = set()
cnt = 0
for i in range(len(txt) - 1):
    new = tuple(sorted([txt[i],txt[i + 1]]))
    m.add(new)
print(len(m))

