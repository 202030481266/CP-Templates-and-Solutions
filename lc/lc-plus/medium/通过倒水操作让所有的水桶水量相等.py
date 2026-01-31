from typing import List
import bisect

class Solution:
    def equalizeWater(self, buckets: List[int], loss: int) -> float:
        l, r = 0, max(buckets)
        n = len(buckets)
        buckets.sort()
        s = [0] * (n+1)
        for i in range(n):
            s[i+1] = s[i] + buckets[i]
        
        def check(val) -> bool:
            # the first element buckets[pos] > val
            pos = bisect.bisect_right(buckets, val) # [0,pos) -> [1,pos+1) = [1,pos]
            return ((s[n]-s[pos])-(n-pos)*val)*((100-loss)/100) >= pos*val - s[pos]
        
        ans = 0
        for i in range(100):
            mid = (l+r)/2
            if (check(mid)):
                ans = mid
                l = mid
            else:
                r = mid
        
        return ans

            