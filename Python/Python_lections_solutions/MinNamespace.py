def mix(*args):

    class Mix:
        def __str__(self):
            ret = []
            for i in sorted(dir(self)):
                if not i.startswith('_') and not callable(getattr(self, i)):
                    ret.append(f"{i}={getattr(self, i)}")
            return ', '.join(ret)
    a = Mix()
    for obj in args:
        for attr in dir(obj):
            if attr.startswith('_') or callable(getattr(obj, attr)):
                continue
            setattr(a, attr, getattr(obj, attr))
    return a

