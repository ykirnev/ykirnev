from itertools import tee
def seesaw(sequence):
    sequence1, sequence2 = tee(sequence)
    a = (x for x in sequence1 if x % 2 == 0)
    b = (x for x in sequence2 if x % 2 != 0)
    flag = True
    a_i = next(a, None)
    b_i = next(b, None)
    while a_i is not None or b_i is not None:
        if flag and a_i is not None:
            yield a_i
            a_i = next(a, None)
        elif not flag and b_i is not None:
            yield b_i
            b_i = next(b, None)
        flag = not flag
