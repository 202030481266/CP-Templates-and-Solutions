from typing import List

class Solution:
    def maxFreeTime(self, eventTime: int, k: int, startTime: List[int], endTime: List[int]) -> int:
        n = len(startTime)
        l = 0
        s = 0
        st = 0
        ans = 0
        for i in range(n):
            s += (endTime[i] - startTime[i])
            while i-l+1 > k:
                s -= (endTime[l] - startTime[l])
                st = endTime[l]
                l += 1
            ed = eventTime if i == n-1 else startTime[i+1]
            ans = max(ans, ed - st - s)
        return ans

            