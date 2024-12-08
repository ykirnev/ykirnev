class Square:
    __match_args__ = ("x", "y", "w")

    def __init__(self, x, y, w):
        self._x = x
        self._y = y
        self._w = w

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        self._x = value

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        self._y = value

    @property
    def w(self):
        return self._w

    @w.setter
    def w(self, value):
        self._w = value

    @property
    def h(self):
        return self._w

    @h.setter
    def h(self, value):
        self._w = value

    @property
    def s(self):
        return self._w ** 2

    @s.setter
    def s(self, value):
        pass

    @property
    def center(self):
        return (self._x + self._w / 2, self._y + self._w / 2)

    @center.setter
    def center(self, value):
        if isinstance(value, tuple) and len(value) == 2:
            cx, cy = value
            self._x = cx - self._w / 2
            self._y = cy - self._w / 2
        elif isinstance(value, tuple) and len(value) == 4:
            cx, cy, dx, dy = value
            self._x = cx + dx - self._w / 2
            self._y = cy + dy - self._w / 2

