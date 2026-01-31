from typing import List


class Solution:
    def minImpossibleOR(self, nums: List[int]) -> int:
        s = set(nums)
        mn = 0
        while (1<<mn) in s:
            mn += 1
        return 1<<mn

        
        