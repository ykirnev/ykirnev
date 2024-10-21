#[1, 2, 3, 0.5, 1.4, "23fegr", True, False, [1, 2, 3, [1,2, 3]]]
#a = list(eval(input())) #через запятую
#a = list(map(int, input().split(";"))) #через пробел и другой разделитель
#a = input().split() #через пробел для строк
#1) вводится количество
n = 0#int(input())
a = []
for i in range(n):
    x = int(input())
    a.append(x)
tmp = 0#int(input())
b = []
while tmp != 0:
    b.append(tmp)
    tmp = int(input())

while tmp != "END":
    b.append(int(tmp))
    tmp = "END" #input()
c = []
#while new := input():
 #   c.append(float(new))
#print(c)
#a = list(map(int, input().split()))
l = len(a)
left = 0
right = l - 1
while (right - left) > 1:
    middle = (right - left) // 2 + left
    if a[middle] < a[middle + 1]:
        left = middle
    else:
        right = middle
    print(right, left)
#print(a[right])
#Ящик с точками
#Вводить вещественные числа x, y и z по три в строке через запятую,
#считая их координатами точек (не менее одной тройки). Конец ввода — пустая строка.
#Вывести минимальный объём содержащего все точки параллелепипеда с рёбрамии,
#параллельными осям координат.
x_min, y_min, z_min = 0, 0, 0
x_max, y_max, z_max = eval(input())
while a:=input():
    x, y, z = eval(a)
    if x < x_min:
        x_min = x
    if y < y_min:
        y_min = y
    if z < z_min:
        z_min = z
    if x > x_max:
        x_max = x
    if y > y_max:
        y_max = y
    if z > z_max:
        z_max = z
print((z_max - z_min)*(x_max - x_min) * (y_max - y_min))

#Сортировка подчсётом
#Вводится последовательность пар натуральных чисел, не превышающих 100,
#последняя строка ввода — пустая. Вывести её в лексикографически отсортированном
#по возрастанию виде. Дополнительные условия: из составных типов данных можно пользоваться
#только списками и кортежами (для вывода — строками), целиком последовательность в памяти
#хранить нельзя!
mas = [[0] * 101 for i in range(101)]
while a:=input():
    x, y = map(int, a.split())
    mas[x][y] += 1
for i in range(101):
    for j in range(101):
        if mas[i][j] != 0:
            for k in range(mas[i][j]):
                print(i, ', ', j)

