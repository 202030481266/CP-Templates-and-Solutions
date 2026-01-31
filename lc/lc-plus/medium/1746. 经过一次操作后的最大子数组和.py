from typing import List

class Solution:
    def maxSumAfterOperation(self, nums: List[int]) -> int:
        # (l, r] = sum[r] - sum[l]
        n = len(nums)
        s1 = [0] * (n+1)
        s2 = [0] * (n+2)
        for i in range(n):
            s1[i+1] = s1[i] + nums[i]
        for i in range(n,0,-1):
            s2[i] = s2[i+1] + nums[i-1]
        
        pre = [0] * (n+1)
        mn = 0
        for i in range(1,n+1):
            # sum[i]
            pre[i] = s1[i] - mn
            if s1[i] < mn:
                mn = s1[i]
        suf = [0] * (n+1)
        mn = 0
        for i in range(n,0,-1):
            # sum[i]
            suf[i] = s2[i] - mn
            if s2[i] < mn:
                mn = s2[i]
        ans = -0x3f3f3f3f
        for i in range(1,n+1):
            res = pre[i] + suf[i] - 2 * nums[i-1] + nums[i-1] * nums[i-1]
            if res > ans:
                ans = res 
        return ans