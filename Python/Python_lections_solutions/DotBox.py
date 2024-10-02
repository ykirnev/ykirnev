x_min, y_min, z_min = eval(input())
x_max, y_max, z_max = x_min, y_min, z_min
while a:= input():
    x, y, z = eval(a)
    if (x_min > x):
        x_min = x
    if (y_min > y):
        y_min = y
    if (z_min > z):
        z_min = z
    if (x_max < x):
        x_max = x
    if (y_max < y):
        y_max = y
    if (z_max < z):
        z_max = z
print((z_max - z_min) * (y_max - y_min) * (x_max - x_min))