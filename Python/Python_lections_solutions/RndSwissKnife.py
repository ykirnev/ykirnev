import random
from collections.abc import Sequence, Iterable


def rnd(a, b=None):
    match (a, b):
        case str() as a, int() as b:
            s = random.randint(0, len(a) - b)
            return a[s:s + b]

        case str() as a, None:
            return random.choice(a.split())

        case str() as a, str() as b:
            return random.choice(a.split(b))

        case int() as a, None:
            return random.randint(0, a)

        case int() as a, int() as b:
            return random.randint(a, b)

        case (float() as a, int() | float() as b) | (int() | float() as a, float() as b):
            return random.random() * (b - a) + a

        case Sequence() as a, None:
            return random.choice(a)

        case Iterable() as a, None:
            return random.choice(list(a))

        case Sequence() as a, int() as b:
            return random.choices(a, k=b)

        case Iterable() as a, int() as b:
            return random.choices(list(a), k=b)



