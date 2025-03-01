from typing import List


class Solution:
    def largestPerimeter(self, nums: List[int]) -> int:
        nums.sort(reverse=True)
        s, n = sum(nums), len(nums)
        for i in range(n-2):
            s -= nums[i]
            if s > nums[i]:
                return s + nums[i]
        return -1 
