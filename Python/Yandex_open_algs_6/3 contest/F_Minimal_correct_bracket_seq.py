def complete_psp(w, s):
    open_brackets = {char for char in w if char in '(['}
    st = []
    result = []

    for char in s:
        if char in open_brackets:
            st.append(char)
        else:
            if st and ((char == ')' and st[-1] == '(') or (char == ']' and st[-1] == '[')):
                st.pop()

    while st:
        open_bracket = st.pop()
        if open_bracket == '(':
            result.append(')')
        else:
            result.append(']')
    return "".join(result)


def generate_minimal_string(n, w, s, result):
    pr = {char: idx for idx, char in enumerate(w)}
    open1 = next(char for char in w if char in '([')
    if open1 == '(':
        close1 = ')'
    else:
        close1 = ']'
    prefix = []
    idx = 0
    while idx < len(result) and pr[result[idx]] < pr[open1]:
        prefix.append(result[idx])
        idx += 1
    gen = list(s) + prefix
    suf_result = result[idx:]
    open_count = (n - len(gen) - len(suf_result)) // 2
    close_count = open_count
    if pr[open1] < pr[close1]:
        gen.extend([open1] * open_count)
        gen.extend([close1] * close_count)
    else:
        for _ in range(open_count):
            gen.append(open1)
            gen.append(close1)
    gen.extend(suf_result)
    return ''.join(gen)


n = int(input())
w = input().strip()
s = input().strip()
result = complete_psp(w, s)
minimal_string = generate_minimal_string(n, w, s, result)
print(minimal_string)