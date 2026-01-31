from typing import List

class Solution:
    def maxPossibleScore(self, start: List[int], d: int) -> int:
        n = len(start)        
        start.sort()

        def check(len: int) -> bool:
            p = start[0]
            for i in range(1,n):
                p = max(p+len, start[i])
                if p > start[i] + d:
                    return False
            return True
        
        l,r = -1,start[-1]+d+1
        while l+1 < r:
            mid = (l+r)//2
            if check(mid):
                l = mid
            else:
                r = mid
        return l
