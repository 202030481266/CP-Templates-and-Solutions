from typing import List

# 细节很多

class Solution:
    def maximumTop(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n == 0:
            return -1
        if k == 0:
            return nums[0]
        if n == 1: # n == 1 and k > 0
            return -1 if k & 1 else nums[0]
        # 判断分类讨论
        if k == 1:
            return nums[1]
        elif k < n:
            return max(max(nums[:k-1]), nums[k])
        elif k == n:
            return max(nums[:k-1])
        return max(nums)