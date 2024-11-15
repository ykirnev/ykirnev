n = int(input())
a = list(map(int, input().split()))
a = [(i, val) for i, val in enumerate(a)]
mas = [-1] * n
st = []
id = -1
for i in range(n):
    if id == -1 or st[id][1] <= a[i][1]:
        st.append(a[i])
        id += 1
    elif st[id][1] > a[i][1]:
        while id >= 0 and st[id][1] > a[i][1]:
            mas[st[id][0]] = a[i][0]
            st.pop()
            id -= 1
        st.append(a[i])
        id += 1
print(*mas)

