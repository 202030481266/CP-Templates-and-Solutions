from typing import List

class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        mx = max(nums)
        n = len(nums)
        l = 0
        cur = 0
        ans = 0
        for v in nums:
            if v == mx:
                cur += 1
            while cur >= k:
                if nums[l] == mx:
                    cur -= 1
                l += 1
            # [0,l)
            ans += l
        return ans
        