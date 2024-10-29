def simple(n):
    k = 2
    while k*k <= n and n % k != 0:
        k += 1
    return (k*k > n)
 
 
def gipersimple(n):
    c = 0
    if simple(n) is False:
        return False
    else:
        for i in range(1, int(len(str(n)))):
            if simple(n % 10**i) is True and simple(n // 10**i) is True:
                c += 1
                return True
                break
        if c == 0:
            return False
 
 
if gipersimple(int(input())) is True:
    print('YES')
else:
    print('NO')