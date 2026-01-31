from typing import List

class Solution:
    def minUnlockedIndices(self, nums: List[int], locked: List[int]) -> int:
        n = len(nums)
        ans = 0
        s = [0]
        for i in range(1,n):
            if nums[s[-1]] < nums[i]:
                s = [i]
            elif nums[s[-1]] == nums[i]:
                s.append(i)
            else:
                if nums[s[-1]] - nums[i] >= 2:
                    return -1
                for v in s:
                    if locked[v]:
                        ans += 1
                nums[i] = nums[s[-1]]
                s = [i]
        return ans