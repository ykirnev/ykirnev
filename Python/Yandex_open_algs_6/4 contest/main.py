for x in range(2):
    for y in range(2):
        for z in range(2):
            f = (x or y) <= (z == x)
            if f == 0:
                pass
                # print(x, z, y)

for x in range(2):
    for y in range(2):
        for z in range(2):
            for w in range(2):
                f = (x and not y) or (y == z) or not w
                if f == 0:
                    pass
                    #print(w, z, y, x)
        # print(x, z, y)
for x in range(2):
    for y in range(2):
        for z in range(2):
            for w in range(2):
                f = ((x <= y) == (y <= z)) and (y or w)
                if f == 1:
                    pass
                    #print(x, z, w, y)
for x in range(2):
    for y in range(2):
        for z in range(2):
            for w in range(2):
                f = ((w <= (not x)) == (z <= y)) and (y or w)
                print(x, w, y, z, f)
