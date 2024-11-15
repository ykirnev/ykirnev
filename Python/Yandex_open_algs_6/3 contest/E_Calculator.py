flag = 1
s = input()
if s[0] == '-':
    s = '0' + s
val = {'+': 1, '-': 1, '*': 2}
st = []
answer = []
s = s.replace('(-', '(0-')
n = len(s)
i = 0
while i < n and flag:
    c = s[i]
    if c not in '+-*()1234567890 ':
        flag = 0
        break
    elif c.isdigit():
        num = c
        i += 1
        while i < n and s[i].isdigit():
            if s[i].isspace():
                flag = 0
                break
            num += s[i]
            i += 1
        answer.append(num)
        continue
    elif c in '+-*':
        while st and st[-1] != '(' and val.get(c, 0) <= val.get(st[-1], 0):
            x = st.pop()
            answer.append(x)
        st.append(c)
    elif c == '(':
        st.append(c)
    elif c == ')':
        while st and st[-1] != '(':
            x = st.pop()
            answer.append(x)
        if not st:
            flag = 0
            break
        st.pop()
    elif c != ' ':
        flag = 0
        break
    i += 1

if flag == 0:
    print("WRONG")
else:
    while st:
        c = st.pop()
        if c in '()':
            flag = 0
            break
        answer.append(c)

    for i in answer:
        if len(i) > 1 or i.isdigit():
            st.append(int(i))
        else:
            if len(st) > 0:
                b = st.pop()
            else:
                flag = 0
                break
            if len(st) > 0:
                a = st.pop()
            else:
                flag = 0
                break
            if i == '+':
                st.append(a + b)
            elif i == '-':
                st.append(a - b)
            elif i == '*':
                st.append(a * b)

    if flag and len(st) == 1:
        print(*st)
    else:
        print("WRONG")
