class Contact:
    def __init__(self, n, p, e):
        self.name = n
        self.phone = p
        self.email = e


def read(inp, m):
    for i in range(len(inp)):
        a, b, c = inp[i].split(',')
        x = Contact(a, b, c)
        m.append(x)
    

def write(m):
    for i in range(len(m)):
        print(m[i].name, end = '')
        print(m[i].phone, end = '')
        print(m[i].email, end = '')


def search_phone(m, request):       
    for i in range(len(m)):
        if request in m[i].phone:
            return(m[i].name, m[i].phone, m[i].email)
        
def search_email(m, request):        
    for i in range(len(m)):
        if request in m[i].email:
            return(m[i].name, m[i].phone, m[i].email)
            

def search_name(m, request):        
    key = False
    for i in range(len(m)):
        if request in m[i].name:
            return (m[i].name, m[i].phone, m[i].email)
    
def search_empty(m):
    for i in range(len(m)):
        if m[i].phone == '' and m[i].email == '':
            print(m[i].name, end = '')
        elif m[i].phone == '':
            print(m[i].name, end = '')
            print(m[i].email, end = '')
        elif m[i].email == '':
            print(m[i].name, end = '')
            print(m[i].phone, end = '')

def edit(m, s):
    ask, number, changeable, new = s.split(',')
    i = int(number)
    if changeable == 'name':
        m[i].name = new
    elif changeable == 'phone':
        m[i].phone = new
    elif changeable == 'email':
        m[i].email = new
    else:
        print("Error")

           
m = []
print("Введите название файла:")
file_name = input()
f = open(file_name, 'r')
inp = f.readlines()
read(inp, m)
print("Для работы c программой:")
print("Для поиска по имени введите search_name и сам запрос через пробел.")
print("Для поиска по телефону введите search_phone и сам запрос через пробел.")
print("Для поиска по почте введите search_email и сам запрос через пробел.")
print("Для поиска по имени введите search_name и сам запрос через пробел.")
print("Для поиска и вывода на экран всех контактов у которых не заполнен номер телефона и/или адрес электронной почты введите search_empty")
print("Редактирование происходит через номер строки")
print("Для редактирования введите edit, номер строки, данные которые хотите поменять(phone для номера телефона, name для имени, email для адреса электронной почты), новые данные - все через запятую")
print("Для прекращения работы введите End")
print("Введите запрос:")
s = input()
while s!='End':
    if 'search_name' in s:
        ask, request = s.split()
        print(*search_name(m, request))
    elif 'search_phone' in s:
        ask, request = s.split()
        print(*search_phone(m, request))
    elif 'search_email' in s:
        ask, request = s.split()
        print(*search_email(m, request))
    elif 'search_empty' == s:
        search_empty(m)
    elif 'edit' in s:
        edit(m, s)
        write(m)
    print("Введите запрос:")
    s = input()