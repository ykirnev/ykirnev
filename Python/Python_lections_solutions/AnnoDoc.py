class AnnoDoc(type):
    def __new__(cls, name, bases, dct):
        orig = dct.get("__doc__", "")
        new = []
        ann = dct.get("__annotations__", {}).copy()
        keys = list(ann.keys())
        for attr in keys:
            a = ann[attr]
            if isinstance(a, str):
                new.append(f"{attr}: {a}")
                if attr in dct:
                    value = dct[attr]
                    ann[attr] = type(value)
                else:
                    del ann[attr]

        if orig:
            dct["__doc__"] = orig + "\n" + "\n".join(new)
        else:
            if new != []:
                dct["__doc__"] = "\n".join(new)
            else:
                dct["__doc__"] = None
        dct["__annotations__"] = ann
        return super().__new__(cls, name, bases, dct)
