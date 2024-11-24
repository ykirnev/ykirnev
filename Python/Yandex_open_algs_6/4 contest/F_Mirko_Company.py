class Employee:
    def __init__(self, id):
        self.id = id
        self.manager = None
        self.subordinates = []
        self.coins = 0

    def add_subordinate(self, subordinate):
        self.subordinates.append(subordinate)
        subordinate.manager = self


class Company:
    def __init__(self, n, managers):
        self.employees = [Employee(i) for i in range(1, n + 1)]
        for i in range(2, n + 1):
            manager_id = managers[i - 2]
            self.employees[manager_id - 1].add_subordinate(self.employees[i - 1])

    def process_task(self):
        task_queue = [self.employees[0]]
        while task_queue:
            current = task_queue.pop()
            if not current.subordinates:
                depth = 1
                temp = current
                while temp:
                    temp.coins += depth
                    depth += 1
                    temp = temp.manager
                if current.manager:
                    current.manager.subordinates.remove(current)
            else:
                task_queue.extend(sorted(current.subordinates, key=lambda x: x.id))
    def get_coins(self):
        return [employee.coins for employee in self.employees]


n = int(input())
if n == 1:
    print(1)
else:
    managers = list(map(int, input().split()))
    company = Company(n, managers)
    while len(company.employees) > 1:
        company.process_task()
    company.process_task()
    print(" ".join(map(str, company.get_coins())))
