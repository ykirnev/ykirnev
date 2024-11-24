import string
import sys

class Pairs:
    __slots__ = ('_start')
    def __init__(self, N):
        self._start = N
    def __getattr__(self, name):
        if name in string.ascii_letters:
            i = string.ascii_letters.index(name) + 1
            l = len(string.ascii_letters)
            val = (self._start + i - 2) % l + 1
            return val

    def __setattr__(self, name, val):
        if name in string.ascii_letters:
            i = string.ascii_letters.index(name) + 1
            step = (val - i) % len(string.ascii_letters)
            self._start = 1 + step
        else:
            super().__setattr__(name, val)

    def __str__(self):
        l = len(string.ascii_letters)
        ans = [None] * l
        for i, c in enumerate(string.ascii_letters):
            val = (self._start + i - 1) % l + 1
            ans[val - 1] = c
        return " ".join(ans)

exec(sys.stdin.read())