import sys
class SizeD:
    def __init__(self):
        self._size = None

    def __get__(self, obj, cls):
        if self._size is not None:
            return self._size
        if hasattr(obj, '__len__'):
            return len(obj)
        if hasattr(obj, '__abs__'):
            return abs(obj)
        return 0

    def __set__(self, obj, value):
        self._size = value

    def __delete__(self, obj):
        self._size = None


def sizer(cls):
    cls.size = SizeD()
    return cls

exec(sys.stdin.read())