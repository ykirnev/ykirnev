def func():
    code = []
    while True:
        try:
            line = input().strip()
            if not line:
                break
            code.append(line)
        except EOFError:
            break
    classes = dict()

    for line in code:
        if line.startswith("class "):
            line = line[:line.find(':')]
            if '(' in line:
                parts = line[len("class "):].split('(')
            else:
                parts = line[len("class "):].split(':')
            name = parts[0].strip()
            base_str = parts[1].strip('):') if len(parts) > 1 else ""
            if ')' in base_str:
                base_str = base_str[:base_str.find(')')]
            base = [b.strip() for b in base_str.split(',')] if base_str else []

            tmp = []
            for i in base:
                if i not in classes:
                    tmp.append([i])
                else:
                    tmp.append(classes[i])

            tmp.append(base)

            result = []
            tmp = [j for j in tmp if j]
            while tmp:
                for value in tmp:
                    candidate = value[0]
                    tmp_flag = True
                    for k in tmp:
                        if candidate in k[1:]:
                            tmp_flag = False
                    if tmp_flag:
                        result.append(candidate)
                        for k in tmp:
                            if k[0] == candidate:
                                k.pop(0)
                        break
                else:
                    return False
                tmp = [j for j in tmp if j]
            classes[name] = [name] + result
    return True


print("Yes" if func() else "No")