def find_modified_max_argmax(L, f):
    i = [x for x in L if type(x) == int]
    if not i:
        return ()
    return max([(f(x), i) for i, x in enumerate(i)])