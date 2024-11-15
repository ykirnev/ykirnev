n, H = map(int, input().split())
heights = list(map(int, input().split()))
widths = list(map(int, input().split()))
combined = {}
for h, w in zip(heights, widths):
    if h in combined:
        combined[h] += w
    else:
        combined[h] = w
heights = list(combined.keys())
widths = list(combined.values())
mx_w = max(widths)
if mx_w >= H:
    print(0)
elif len(heights) == 1:
    print(0)
else:
    n = len(heights)
    chairs = sorted([(heights[i], widths[i]) for i in range(n)], key=lambda x: (x[0], -x[1]))
    diffs = []
    mx = 0
    total_width = chairs[0][1]
    prev = chairs[0][0]
    for i in range(1, n):
        dif = abs(chairs[i][0] - prev)
        diffs.append(dif)
        prev = chairs[i][0]
        if mx < dif:
            mx = dif
        total_width += chairs[i][1]

    diffs = sorted([(diffs[i], i) for i in range(n - 1)], key=lambda x: (-x[0], x[1]))
    max_ids = [(diffs[0][0], 0, n - 1)]
    i = 0
    for j in range(1, n - 1):
        i += 1
        if diffs[i][0] == diffs[i - 1][0]:
            max_ids.append((diffs[i][0], min(diffs[i][1], diffs[i - 1][1]), max(diffs[i][1], diffs[i - 1][1])))
        else:
            prev = diffs[i - 1][0]
            prev_l = max_ids[i - 1][1]
            prev_r = max_ids[i - 1][2]
            prev_id = diffs[i - 1][1]
            idx = diffs[i][0]
            idx_id = diffs[i][1]
            if prev_id == prev_l:
                prev_id = prev_r
            if idx_id > prev_r or idx_id < prev_l:
                l = prev_l
                r = prev_r
                idx = prev
            elif idx_id < prev_id:
                l = prev_l
                r = prev_id - 1
            else:
                l = prev_id + 1
                r = prev_r

            max_ids.append((idx, l, r))


    left = 0
    right = n - 1
    i = -1
    n = len(max_ids)
    while total_width >= H and i < (n - 2):
        i += 1
        left_new = max_ids[i][1]
        right_new = max_ids[i][2]
        for j in range(left, left_new):
            total_width -= chairs[j][1]
        for j in range(right, right_new, -1):
            total_width -= chairs[j][1]
        left = left_new
        right = right_new
    if n == 2 and i == 0:
        i += 1
        left_new = max_ids[i][1]
        right_new = max_ids[i][2]
        for j in range(left, left_new):
            total_width -= chairs[j][1]
        for j in range(right, right_new, -1):
            total_width -= chairs[j][1]
        total_width += chairs[1][1]
        if total_width >= H:
            print(max_ids[1][0])
        else:
            print(max_ids[0][0])
    elif i == -1 or i == 0:
        if chairs[0][1] < H and chairs[1][1] < H:
            print(max_ids[0][0])
        else:
            print(0)
    elif i == n - 1:
        print(0)
    else:
        if max_ids[i] == max_ids[i + 1] and (i + 2) != len(max_ids):
            print(max_ids[i - 1][0])
        else:
            print(max_ids[i][0])
    print(max_ids)
    print(diffs)
