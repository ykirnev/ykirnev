def check(s, filename):
    words = s.lower().split()
    vocab = {}
    for x in words:
        if x in vocab:
            vocab[x] += 1
        else:
            vocab[x] = 1
    words = sorted(vocab.keys())
    with open(filename, 'w') as file:
        for x in words:
            file.write(f"{x} {vocab[x]}\n")