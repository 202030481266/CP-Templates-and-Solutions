from typing import List

class Solution:
    def isPossible(self, nums: List[int]) -> bool:
        n = len(nums)
        val = [0] * n
        l, r = -1, -1
        i = 0
        while i < n:
            j = i + 1
            while j < n and nums[j] == nums[i]:
                j += 1
            if l != -1 and nums[i] - nums[l] != 1:
                for k in range(l, r):
                    if val[k] < 3:
                        return False
                l, r = -1, -1
            if j - i < r - l:
                for k in range(l + (j - i), r):
                    if val[k] < 3:
                        return False
                for x, k in zip(range(l, l + (j - i)), range(i, j)):
                    val[k] = val[x] + 1
            elif j - i > r - l:
                for k in range(i, i + (j - i) - (r - l)):
                    val[k] = 1
                for x, k in zip(range(l, r), range(i + (j - i) - (r - l), j)):
                    val[k] = val[x] + 1
            else:
                for x, k in zip(range(l, r), range(i, j)):
                    val[k] = val[x] + 1
            l, r = i, j
            i = j
        for k in range(l, r):
            if val[k] < 3:
                return False
        return True
            