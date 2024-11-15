m = int(input())
st = []
pr = [0]
id_pr = 1
sum_del = 0
cnt_del = 0
for i in range(m):
    a = input()
    if a == '-':
        x = st.pop()
        pr.pop()
        id_pr -= 1
        print(x)
    elif a[0] == '+':
        num = int(a[1:])
        st.append(num)
        pr.append(pr[-1]+num)
        id_pr += 1
    elif a[0] == '?':
        del_in_row = 0
        k = int(a[1:])
        sm = pr[id_pr - 1]  - pr[id_pr  - k - 1]
        print(sm)