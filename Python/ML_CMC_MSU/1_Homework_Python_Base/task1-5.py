from typing import List
import itertools

def hello(x=None):
    if x is None or x == '':
        return "Hello!"
    else:
        return f"Hello, {x}!"


def int_to_roman(x):
    if not (1 <= x <= 3999):
        exit()
    numbers = { 1000: 'M', 900: 'CM', 500: 'D', 400: 'CD',
               100: 'C', 90: 'XC', 50: 'L', 40: 'XL',
               10: 'X', 9: 'IX', 5: 'V', 4: 'IV', 1: 'I'
    }
    res = []
    for val, rome in numbers.items():
        while x >= val:
            res.append(rome)
            x -= val
    return ''.join(res)


def longest_common_prefix(x):
    if not x:
        return ""
    min = 1000000
    x = [s.lstrip() for s in x]
    for s in x:
        s.lstrip
        if (len(s) < min):
            min = len(s)
            min_s = s
    id = len(min_s)
    for s in x:
        for i in range(len(min_s)):
            if s[i] != min_s [i] and id > i:
                id = i
                break
    return min_s[:id]

def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True

def primes():
    num = 2
    while True:
        if is_prime(num):
            yield num
        num += 1


class BankCard:
    def __init__(self, total_sum, balance_limit=None):
        self.total_sum = total_sum
        self.balance_limit = balance_limit

    def __call__(self, sum_spent):
        if sum_spent > self.total_sum:
            raise ValueError(f"Not enough money to spend {sum_spent} dollars.")
        self.total_sum -= sum_spent
        print(f"You spent {sum_spent} dollars.")

    def __str__(self):
        return "To learn the balance call balance."

    @property
    def balance(self):
        if self.balance_limit is not None:
            if self.balance_limit <= 0:
                raise ValueError("Balance check limits exceeded.")
            self.balance_limit -= 1
        return self.total_sum

    def put(self, sum_put):
        self.total_sum += sum_put
        print(f"You put {sum_put} dollars.")

    def __add__(self, other):
        new_total_sum = self.total_sum + other.total_sum
        new_balance_limit = max(self.balance_limit, other.balance_limit) if self.balance_limit is not None and other.balance_limit is not None else None
        return BankCard(new_total_sum, new_balance_limit)