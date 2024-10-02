def superposition(funmod, funseq):
    def new (f):
        def res(x):
            return funmod(f(x))
        return res
    return [new(f) for f in funseq]