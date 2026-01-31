levels = {
    "Year": 0,
    "Month": 1,
    "Day": 2,
    "Hour": 3,
    "Minute": 4,
    "Second": 5
}
class LogSystem:

    def __init__(self):
        self.logs = []
        self.ids = []

    def put(self, id: int, timestamp: str) -> None:
        f = False
        t = timestamp.split(':')
        for i in range(len(self.ids)):
            if self.ids[i] == id and self.logs[i] == t:
                return 
        self.logs.append(t)
        self.ids.append(id)

    def retrieve(self, start: str, end: str, granularity: str) -> List[int]:
        ed = levels[granularity]
        ans = []
        s_t = start.split(':')
        e_t = end.split(':')
        for i in range(len(self.logs)):
            id,t = self.ids[i],self.logs[i]
            flag = True
            for i in range(ed+1):
                if t[i] < s_t[i]:
                    flag = False
                    break
                elif t[i] > s_t[i]:
                    break
            for i in range(ed+1):
                if t[i] > e_t[i]:
                    flag = False
                    break
                elif t[i] < e_t[i]:
                    break
            if flag:
                ans.append(id)
        return ans
                


# Your LogSystem object will be instantiated and called as such:
# obj = LogSystem()
# obj.put(id,timestamp)
# param_2 = obj.retrieve(start,end,granularity)