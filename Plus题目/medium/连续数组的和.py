mod = 10**9 + 7

class Solution:
    def getSum(self, nums: List[int]) -> int:
        n = len(nums)
        sum = [0]*(n+1)
        for i in range(n):
            sum[i+1] = (sum[i] + nums[i]) % mod
        # we need to know that sum of [l,i] + [l+1, i] + [l+2, i] ... [i,i]
        for i in range(1,n+1):
            sum[i] = (sum[i] + sum[i-1]) % mod
        pre1, pre2 = 0, 0
        ans = 0
        for i in range(1,n+1):
            if i == 1:
                ans = (ans + sum[i]) % mod
                pre1 = 1
                pre2 = 1
            else:
                x = 1 
                y = 1
                if nums[i-1] == nums[i-2] + 1:
                    if pre1 + 1 > x:
                        x = pre1 + 1
                if nums[i-1] == nums[i-2] - 1:
                    if pre2 + 1 > y:
                        y = pre2 + 1
                mx = x if x > y else y
                s = ((sum[i]-sum[i-1]) * mx) % mod
                if i-mx == 0:
                    ans = (ans + s - sum[i-1]) % mod
                else:
                    ans = (ans + s - (sum[i-1]-sum[i-mx-1])) % mod
                pre1, pre2 = x, y
        return ans % mod