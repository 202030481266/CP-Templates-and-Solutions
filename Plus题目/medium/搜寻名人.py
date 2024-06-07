# The knows API is already defined for you.
# return a bool, whether a knows b
# def knows(a: int, b: int) -> bool:

class Solution:
    def findCelebrity(self, n: int) -> int:
        a = -1
        for i in range(n):
            if a == -1:
                a = i
            else:
                x,y = knows(a,i), knows(i,a)
                if (x and y) or (not x and not y):
                    a = -1 # 互相认识或者都不认识
                elif x:
                    a = i # a 知道 i
        if a == -1:
            return -1
        for i in range(n):
            if i == a:
                continue
            if not knows(i,a) or knows(a,i):
                return -1
        return a
        