from typing import List

class Solution:
    def minTime(self, time: List[int], m: int) -> int:
        n = len(time)
        
        def check(t) -> bool:
            c = m
            i = 0
            while i < n and c:
                c -= 1
                s = 0
                mx = 0
                while i < n and s + time[i] <= t:
                    s += time[i]
                    if time[i] > mx:
                        mx = time[i]
                    i += 1
                if i < n and mx < time[i]:
                    mx = time[i]
                s -= mx
                while i < n and s + time[i] <= t:
                    s += time[i]
                    i += 1
            return i == n
        
        l, r = -1, sum(time)
        while l + 1 < r:
            mid = (l + r) >> 1
            if check(mid):
                r = mid
            else:
                l = mid
        return r
                
                