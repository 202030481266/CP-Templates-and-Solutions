
class MyCalendarTwo:

    def __init__(self):
        self.calendar = []

    def book(self, startTime: int, endTime: int) -> bool:
        arr = []
        for s, e in self.calendar:
            arr.append((s, 1))
            arr.append((e, -1))
        arr.append((startTime, 1))
        arr.append((endTime, -1))
        arr.sort()
        cnt = 0
        for s, v in arr:
            cnt += v
            if cnt >= 3:
                return False
        self.calendar.append((startTime, endTime))
        return True
        
            


# Your MyCalendarTwo object will be instantiated and called as such:
# obj = MyCalendarTwo()
# param_1 = obj.book(startTime,endTime)