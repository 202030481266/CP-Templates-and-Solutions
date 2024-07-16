# it is not so easy to get this idea of greedy algorithm
# provement:
# a1, a2, a3, a4, a5, a6, a7, a8, a9, a10
# assume a3,a4,a5 merged and a8,a9,a10 merged is one of the optimized solution: a1, a2, a3*a4*a5, a6, a7, a8*a9*a10
# if a1*a2 can merged, then we could merge a1*a2, ans is better
# else if a2*a3 can merged, then we could merge a2*a3, then we get current solution: a1, a2*a3, a4*a5, a6, a7, a8*a9*a10
# Now, ans is not worse than the optimizied solution and we may get a better solution if a2*a3*a4*a5 can merged
# we always get a non-worse solution, so we could get the optimized solution

class Solution:
    def minArrayLength(self, nums: List[int], k: int) -> int:
        if min(nums) == 0:
            return 1
        n = len(nums)
        i = 0
        ans = 0
        while i < n:
            j = i+1
            cur = nums[i]
            while j < n and cur * nums[j] <= k:
                cur *= nums[j]
                j += 1
            ans += 1
            i = j 
        return ans
        