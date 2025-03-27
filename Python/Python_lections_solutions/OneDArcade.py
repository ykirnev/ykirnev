import asyncio
import sys

class Monster:
    def __init__(self, name, position, delay, power):
        self.name = name
        self.position = position
        self.delay = delay
        self.power = power
        self.alive = True
        self.cnt = 0

    async def run(self, event_start, event_end):
        while True:
            await event_start.wait()
            self.cnt += 1
            if self.alive and (self.cnt % self.delay) == 0:
                self.position += 1
            await event_end.wait()


async def game(monsters, event_start, event_end, eps):
    for _ in range(eps):
        await event_start.wait()
        await event_end.wait()
        alive_monsters = [m for m in monsters if m.alive]
        if not alive_monsters:
            return "All dead"
        if len(alive_monsters) == 1:
            return alive_monsters[0].name
        position_dict = {}
        fighter1 = None
        fighter2 = None
        for i, monster in enumerate(alive_monsters):
            i1 = monster.position
            if i1 in position_dict:
                fighter1 = position_dict[i1]
                fighter2 = i
                break
            position_dict[i1] = i

        if fighter1 is not None and fighter2 is not None:
            m1, m2 = alive_monsters[fighter1], alive_monsters[fighter2]
            if m1.power == m2.power:
                m1.alive = False
                m2.alive = False
            elif m1.power > m2.power:
                m1.power -= m2.power
                m2.alive = False
            else:
                m2.power -= m1.power
                m1.alive = False
    alive = [m.name for m in monsters if m.alive]
    if len(alive) == len(monsters):
        return "All flee"
    elif not alive:
        return "All dead"
    return ", ".join(alive)

exec(sys.stdin.read())