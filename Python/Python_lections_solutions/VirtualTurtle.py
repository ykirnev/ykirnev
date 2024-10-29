def turtle(coord, way):
    x, y = coord
    ways = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    cur = way
    while True:
        a = yield (x, y)
        if a == "f":
            dx, dy = ways[cur]
            x += dx
            y += dy
        elif a == "l":
            cur = (cur + 1) % 4
        elif a == "r":
            cur = (cur - 1) % 4
