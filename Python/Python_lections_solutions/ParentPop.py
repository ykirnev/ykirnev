import sys
class Sire:
    @property
    def parent(self):
        return self.__class__.__bases__[0].__name__
exec(sys.stdin.read())