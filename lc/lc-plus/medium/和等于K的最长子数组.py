class Solution:
    def maxSubArrayLen(self, nums: List[int], k: int) -> int:
        d = {0:-1}
        s = 0
        ans = 0
        for i in range(len(nums)):
            s += nums[i]
            if d.get(s-k) is not None:
                ans = max(ans, i-d[s-k])
            if d.get(s) is None:
                d[s] = i
        return ans        
        