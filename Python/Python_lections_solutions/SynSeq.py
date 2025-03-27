import random
import asyncio

class Seq:
    _ord = 0
    _done = 0
    _events = []

    def __init__(self, name):
        self.name = name
        self._o = Seq._ord
        Seq._ord += 1
        Seq._events.append(asyncio.Event())
        if self._o == 0:
            Seq._events[0].set()

    async def run(self):
        await Seq._events[self._o].wait()
        print(self.name)
        Seq._done += 1
        if self._o + 1 < len(Seq._events):
            Seq._events[self._o + 1].set()
        return self.name

