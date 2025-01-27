from typing import List

class Solution:
    def maxSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        mn = nums[0]
        for i in range(1, n):
            mn &= nums[i]
        i = 0
        ans = 0
        while i < n:
            j = i+1
            cur = nums[i]
            while j < n and cur > 0:
                cur &= nums[j]
                j += 1
            if cur > 0:
                break
            ans += 1
            i = j
        return 1 if ans == 0 else ans