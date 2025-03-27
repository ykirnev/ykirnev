import asyncio
import sys
class FilterQueue(asyncio.Queue):
    @property
    def window(self):
        if self.empty():
            return None
        return self._queue[0]

    def __contains__(self, filter):
        return any(filter(item) for item in self._queue)

    def later(self):
        if self.empty():
            raise asyncio.QueueEmpty
        self._queue.append(self._queue.popleft())

    async def get(self, filter=None):
        if filter is None:
            return await super().get()
        while True:
            for _ in range(len(self._queue)):
                if filter(self._queue[0]):
                    return await super().get()
                self.later()
            return await super().get()

exec(sys.stdin.read())