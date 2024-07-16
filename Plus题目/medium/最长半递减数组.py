class Solution:
    def maxSubarrayLength(self, nums: List[int]) -> int:
        # 序列性问题
        n = len(nums)
        if n < 2: 
            return 0
        if nums[0] > nums[n-1]: # it is useful case
            return n
        mn = [0x3f3f3f3f for _ in range(n)]
        mn[n-1] = nums[n-1]
        for i in range(n-2,-1,-1):
            mn[i] = nums[i] if nums[i] < mn[i+1] else mn[i+1]
        l, r = 0, 1
        ans = 0
        while r < n and l <= r:
            # [l, r)
            if l == r:
                r = l + 1
            while r < n and mn[r] < nums[l]:
                r += 1
            if l+1 < r and r-l > ans:
                ans = r-l
            l += 1
        return ans
            
