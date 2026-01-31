'''
    userid : tasklist
    tasklist : taskid, tags
'''
from collections import defaultdict

class TodoList:

    def __init__(self):
        self.users = defaultdict(list)
        self.ids = 1

    def addTask(self, userId: int, taskDescription: str, dueDate: int, tags: List[str]) -> int:
        self.users[userId].append([dueDate, taskDescription, tags, False, self.ids])
        self.ids += 1
        return self.ids - 1

    def getAllTasks(self, userId: int) -> List[str]:
        res = []
        self.users[userId].sort(key=lambda x : x[0])
        for task in self.users[userId]:
            if not task[3]:
                res.append(task[1])
        return res
            
    def getTasksForTag(self, userId: int, tag: str) -> List[str]:
        res = []
        self.users[userId].sort(key=lambda x : x[0])
        for task in self.users[userId]:
            if not task[3] and tag in task[2]:
                res.append(task[1])
        return res

    def completeTask(self, userId: int, taskId: int) -> None:
        n = len(self.users[userId])
        for i in range(n):
            if self.users[userId][i][4] == taskId:
                self.users[userId][i][3] = True



# Your TodoList object will be instantiated and called as such:
# obj = TodoList()
# param_1 = obj.addTask(userId,taskDescription,dueDate,tags)
# param_2 = obj.getAllTasks(userId)
# param_3 = obj.getTasksForTag(userId,tag)
# obj.completeTask(userId,taskId)