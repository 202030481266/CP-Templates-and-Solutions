from typing import List

class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)

        def check(k: int) -> bool:
            s = [0] * (n + 1)
            for i in range(k):
                l, r, val = queries[i]
                s[l] += val
                s[r + 1] -= val
            cur = 0
            for i in range(n):
                cur += s[i]
                if cur < nums[i]:
                    return False
            return True
        
        l, r = -1, len(queries)+1
        while l + 1 < r:
            mid = (l + r) >> 1
            if check(mid): r = mid
            else: l = mid
        
        return r if r < len(queries)+1 else -1