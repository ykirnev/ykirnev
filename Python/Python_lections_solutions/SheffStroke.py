def sheff(A, B):
    if not(A) and not(B):
        return True
    elif A and B:
        return False
    elif A:
        return A
    return B