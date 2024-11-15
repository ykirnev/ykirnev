s = input()
st = []
mas = s.split()
for i in mas:
    if i.isdigit():
        st.append(int(i))
    else:
        b = st.pop()
        a = st.pop()
        if i == '+':
            st.append(a + b)
        elif i == '-':
            st.append(a - b)
        elif i == '*':
            st.append(a * b)
print(*st)
