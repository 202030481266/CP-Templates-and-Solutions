class Solution:
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        # dp
        n = len(nums)
        pre = [0] * (n+1)
        for i in range(n):
            pre[i+1] = pre[i] + nums[i]
        # find the maximum one that abs(nums[i] - nums[j]) == k
        # (j, i] = pre[i] - pre[j]
        mn = {}
        ans = -10**15
        for i, a in enumerate(nums):
            if a - k in mn:
                ans = max(ans, pre[i+1] - mn[a - k])
            if a + k in mn:
                ans = max(ans, pre[i+1] - mn[a + k])
            if a in mn:
                mn[a] = min(mn[a], pre[i])
            else:
                mn[a] = pre[i]
        return 0 if ans == -10**15 else ans