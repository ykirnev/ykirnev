from itertools import cycle
def speed(path, stops, times):
    path_i = iter(path)
    stops_i = cycle(stops)
    times_i = iter(times)
    while True:
        cnt = next(stops_i)
        dst = 0
        for _ in range(cnt):
            new = next(path_i, None)
            if new is None:
                dst += 0
            else:
                dst += new
        if dst == 0:
            return
        time = next(times_i, None)
        if time is None:
            return
        yield dst / time
    return

