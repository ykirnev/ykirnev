class ExceptionTree:
    def __init__(self):
        self.exceptions = {}
    def __call__(self, n):
        if n not in self.exceptions:
            parent = self(n // 2) if n // 2 > 0 else Exception
            exc = type(f'Exception-{n}', (parent,), {'n': n})
            self.exceptions[n] = exc
        return self.exceptions[n]
