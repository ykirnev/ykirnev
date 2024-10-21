import math
def distance(xyz1, xyz2):
    x1, y1, z1 = xyz1
    x2, y2, z2 = xyz2
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2 + (z2 - z1) ** 2)

galaxies = {}
while a:=input():
    if ' ' not in a:
        break
    x, y, z, name = a.split()
    xyz = (float(x), float(y), float(z))
    galaxies[xyz] = name
mx = -1
galaxy_pair = None
xyz = list(galaxies.keys())
for i in range(len(xyz)):
    for j in range(i + 1, len(xyz)):
        coord1 = xyz[i]
        coord2 = xyz[j]
        dist = distance(coord1, coord2)
        if dist > mx:
            mx = dist
            galaxy_pair = (galaxies[coord1], galaxies[coord2])
res = sorted(galaxy_pair)
print(res[0], res[1])