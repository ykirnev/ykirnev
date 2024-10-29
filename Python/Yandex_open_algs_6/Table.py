def trans_tablo(tablo):
    while tablo and all(cell == '.' for cell in tablo[0]):
        tablo.pop(0)
    while tablo and all(cell == '.' for cell in tablo[-1]):
        tablo.pop()
    if not tablo:
        return tablo
    left = 0
    while left < len(tablo[0]) and all(row[left] == '.' for row in tablo):
        left += 1
    right = len(tablo[0]) - 1
    while right >= 0 and all(row[right] == '.' for row in tablo):
        right -= 1

    transformed_tablo = []
    for row in tablo:
        transformed_tablo.append(row[left:right + 1])

    return transformed_tablo


def check_I(tablo):
    return all(cell == '#' for row in tablo for cell in row)


def check_O(tablo):
    n = len(tablo)
    m = len(tablo[0]) if n > 0 else 0
    top, bottom, left, right = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '#':
                if top is None:
                    top = i
                bottom = i
                if left is None or j < left:
                    left = j
                if right is None or j > right:
                    right = j
    if top is None or bottom is None:
        return False
    top_in, bottom_in, left_in, right_in = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '.':
                if top_in is None:
                    top_in = i
                bottom_in = i
                if left_in is None or j < left_in:
                    left_in = j
                if right_in is None or j > right_in:
                    right_in = j
    for i in range(top_in, bottom_in + 1):
        for j in range(left_in, right_in + 1):
            if tablo[i][j] != '.':
                return False
    if (top_in > top) and (bottom > bottom_in) and (left < left_in) and (right > right_in):
        return True
    return False

def check_C(tablo):
    n = len(tablo)
    m = len(tablo[0]) if n > 0 else 0
    top, bottom, left, right = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '#':
                if top is None:
                    top = i
                bottom = i
                if left is None or j < left:
                    left = j
                if right is None or j > right:
                    right = j
    if top is None or bottom is None:
        return False
    top_in, bottom_in, left_in, right_in = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '.':
                if top_in is None:
                    top_in = i
                bottom_in = i
                if left_in is None or j < left_in:
                    left_in = j
                if right_in is None or j > right_in:
                    right_in = j
    for i in range(top_in, bottom_in + 1):
        for j in range(left_in, right_in + 1):
            if tablo[i][j] != '.':
                return False
    if (top_in > top) and (bottom > bottom_in) and (left < left_in) and (right == right_in):
        return True
    return False

def check_L(tablo):
    n = len(tablo)
    m = len(tablo[0]) if n > 0 else 0
    top, bottom, left, right = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '#':
                if top is None:
                    top = i
                bottom = i
                if left is None or j < left:
                    left = j
                if right is None or j > right:
                    right = j
    if top is None or bottom is None:
        return False
    top_in, bottom_in, left_in, right_in = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '.':
                if top_in is None:
                    top_in = i
                bottom_in = i
                if left_in is None or j < left_in:
                    left_in = j
                if right_in is None or j > right_in:
                    right_in = j
    for i in range(top_in, bottom_in + 1):
        for j in range(left_in, right_in + 1):
            if tablo[i][j] != '.':
                return False
    if (top_in == top) and (bottom > bottom_in) and (left < left_in) and (right == right_in):
        return True
    return False


def check_H(tablo):
    n = len(tablo)
    m = len(tablo[0]) if n > 0 else 0
    top, bottom, left, right = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '#':
                if top is None:
                    top = i
                bottom = i
                if left is None or j < left:
                    left = j
                if right is None or j > right:
                    right = j
    if top is None or bottom is None:
        return False
    if not (all(tablo[i][left] == '#' for i in range(top, bottom + 1)) and
            all(tablo[i][right] == '#' for i in range(top, bottom + 1))):
        return False
    top_in, bottom_in, left_in, right_in = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '.':
                if top_in is None:
                    top_in = i
                bottom_in = i
                if left_in is None or j < left_in:
                    left_in = j
                if right_in is None or j > right_in:
                    right_in = j
    horizontal_connection_found = False
    i = top
    hor_id = 0
    hor_first_id = 0
    while i < bottom + 1:
        if all(tablo[i][j] == '#' for j in range(left, right + 1)):
            if horizontal_connection_found:
                return False
            horizontal_connection_found = True
            hor_first_id = i
            hor_id = i
            i += 1
            while all(tablo[i][j] == '#' for j in range(left, right + 1)) and i < bottom - 1:
                hor_id = i
                i += 1
        i += 1
    if hor_id == bottom:
        return False
    for i in range(hor_first_id):
        for j in range(left_in, right_in + 1):
            if tablo[i][j] != '.':
                return False
    return horizontal_connection_found

def check_P(tablo):
    n = len(tablo)
    m = len(tablo[0]) if n > 0 else 0
    top, bottom, left, right = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '#':
                if top is None:
                    top = i
                bottom = i
                if left is None or j < left:
                    left = j
                if right is None or j > right:
                    right = j
    if top is None or bottom is None:
        return False
    top_in, bottom_in, left_in, right_in = None, None, None, None
    for i in range(n):
        for j in range(m):
            if tablo[i][j] == '.':
                if top_in is None:
                    top_in = i
                bottom_in = i
                if left_in is None or j < left_in:
                    left_in = j
                if right_in is None or j > right_in:
                    right_in = j
    horizontal_connection_found = False
    id = 0
    for i in range(n):
        if all(tablo[i][j] == '#' for j in range(left, right + 1)):
            id += 1
        else:
            break
    if id == 0:
        return False
    i = id
    hor_id = 0
    hor_first_id = 0
    while i < bottom + 1:
        if all(tablo[i][j] == '#' for j in range(left, right + 1)):
            if horizontal_connection_found:
                return False
            horizontal_connection_found = True
            hor_first_id = i
            hor_id = i
            while all(tablo[i][j] == '#' for j in range(left, right + 1)) and i < bottom - 1:
                hor_id = i
                i += 1
        i += 1
    if hor_id == bottom:
        return False
    if not (all(tablo[i][left] == '#' for i in range(top, bottom + 1)) and
            all(tablo[i][right] == '#' for i in range(top, hor_id))):
        return False
    for j in range(left_in, right + 1):
        for i in range(hor_id + 2, bottom + 1):
            if tablo[i][j] != '.':
                return False
    for j in range(left_in, right_in):
        for i in range(top_in, hor_first_id):
            if tablo[i][j] != '.':
                return False
    return horizontal_connection_found



n = int(input())
tablo = [input().strip() for _ in range(n)]
transformed_tablo = trans_tablo(tablo)
if not transformed_tablo:
    print('X')
elif check_I(transformed_tablo):
    print('I')
elif check_O(transformed_tablo):
    print('O')
elif check_C(transformed_tablo):
    print('C')
elif check_L(transformed_tablo):
    print('L')
elif check_H(transformed_tablo):
    print('H')
elif check_P(transformed_tablo):
    print('P')
else:
    print('X')