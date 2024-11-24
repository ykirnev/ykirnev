from fractions import Fraction
import math

class Sausage:
    def __init__(self, word="pork!", n=1):
        self.word = word if isobj(word, str) else "pork!"
        self.n = Fraction(n) if isobj(n, (int, float, Fraction, str)) else Fraction(1)
        if self.n < 0:
            self.n = Fraction(0)


    def __str__(self):
        full_units = self.n //1
        remainder = self.n % 1
        full_batons = math.floor(full_units)
        partial_size = math.floor(remainder * 12)
        batons = []
        batons.append(self._draw_batons(full_batons, partial_size))
        return "".join(batons)

    def _draw_batons(self, full, extra):
        size = 12
        top = ''
        middle = ''
        bottom = ''
        if full == 0 and extra == 0:
            top = '/|\n'
            middle = '||\n'
            bottom = '\\|'
            batons = []
            batons.append(top)
            batons.append(middle)
            batons.append(middle)
            batons.append(middle)
            batons.append(bottom)
            return "".join(batons)
        for i in range(full):
            top += '/' + '-' * 12 + "\\"
            middle += "|" + self.word * (size // len(self.word)) + self.word[:size % len(self.word)] + "|"
            bottom += '\\' + '-' * 12 + "/"
        if extra != 0:
            top += '/' + '-' * extra + "|"
            middle += "|" + self.word * (extra // len(self.word)) + self.word[:extra % len(self.word)] + "|"
            bottom += '\\' + '-' * extra + "|"
        top += '\n'
        middle += '\n'
        batons = []
        batons.append(top)
        batons.append(middle)
        batons.append(middle)
        batons.append(middle)
        batons.append(bottom)
        return "".join(batons)

    def __add__(self, other):
        return Sausage(self.word, self.n + other.n)

    def __sub__(self, other):
        new = self.n - other.n
        return Sausage(self.word, max(new, 0))


    def __mul__(self, factor):
        return Sausage(self.word, self.n * factor)

    def __rmul__(self, factor):
        return self * factor

    def __truediv__(self, divisor):
        return Sausage(self.word, self.n / divisor)

    def __abs__(self):
        return abs(self.n)

    def __bool__(self):
        return self.n > 0
