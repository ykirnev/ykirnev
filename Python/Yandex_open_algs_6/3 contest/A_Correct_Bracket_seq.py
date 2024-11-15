s = input()
st = []
if len(s) == 0:
    print('yes')
else:
    st.append(s[0])
    id = 0
    flag = 1
    for i in range(1, len(s)):
        tmp = s[i]
        if tmp in '[{(':
            id += 1
            st.append(tmp)
        elif id < 0:
            flag = 0
            break
        elif tmp == ')':
            if st[id] == '(':
                id -= 1
                st.pop()
            else:
                flag = 0
                break
        elif tmp == '}':
            if st[id] == '{':
                id -= 1
                st.pop()
            else:
                flag = 0
                break
        elif tmp == ']':
            if st[id] == '[':
                id -= 1
                st.pop()
            else:
                flag = 0
                break
    if flag and len(st) == 0:
        print('yes')
    else:
        print('no')

