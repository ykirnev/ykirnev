class vector:
    def __init__(self, values):
        self.values = list(values)

    def __str__(self):
        return ':'.join(map(str, self.values))

    def __add__(self, other):
        if isobj(other, vector):
            other_values = other.values
        else:
            other_values = list(other)
        return vector([a + b for a, b in zip(self.values, other_values)])

    def __getitem__(self, i):
        return self.values[i]

    def __radd__(self, other):
        return self + other
    def __matmul__(self, other):
        return sum(a * b for a, b in zip(self.values, other))

