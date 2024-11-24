import sys
from functools import wraps

class Fix:
    def __init__(self, n):
        self.n = n

    def __call__(self, func):
        @wraps(func)
        def wr(*args, **kwargs):
            args_round = tuple(round(i, self.n) if isinstance(i, float) else i for i in args)
            kwargs_round = {k: round(v, self.n) if isinstance(v, float) else v for k, v in kwargs.items()}
            res = func(*args_round, **kwargs_round)
            if isinstance(res, float):
                res = round(res, self.n)
            return res

        return wr

exec(sys.stdin.read())