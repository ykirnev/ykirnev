class NegExt:
    def __neg__(self):
        for base in self.__class__.mro()[1:]:
            try:
                result = super().__neg__()
                return self.__class__(result)
            except AttributeError:
                pass

            try:
                result = super().__getitem__(slice(1, -1))
                return self.__class__(result)
            except (AttributeError, TypeError, KeyError):
                pass
        return self.__class__(self)