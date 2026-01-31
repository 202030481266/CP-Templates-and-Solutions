from typing import List

class Solution:
    def minLengthAfterRemovals(self, nums: List[int]) -> int:
        n = len(nums)
        i = 0
        mx = 0
        s = 0
        while i < n:
            j = i+1
            while j < n and nums[j] == nums[i]:
                j += 1
            s += j-i
            if j-i > mx:
                mx = j-i
            i = j
        cnt = s-mx if s-mx < mx else s//2
        return n-cnt*2