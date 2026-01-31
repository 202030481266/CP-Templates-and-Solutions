class Solution:
    def maxKDistinct(self, nums: List[int], k: int) -> List[int]:
        nums.sort(reverse=True)
        i = 0
        ans = []
        n = len(nums)
        while i < n:
            j = i + 1
            while j < n and nums[j] == nums[i]:
                j += 1
            ans.append(nums[i])
            i = j
        return ans[:k]