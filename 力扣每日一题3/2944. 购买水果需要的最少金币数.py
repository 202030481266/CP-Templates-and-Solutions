from typing import List

class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)
        # no greedy , should be dp
        # 单调队列
        arr = [0] * (n + 1)
        dp = [0x3f3f3f3f] * (n + 1)
        dp[0] = 0
        dp[1] = prices[0]
        l, r = 0, 1 # [l,r)
        arr[l] = 1
        for i in range(2, n+1):
            while l < r and dp[i-1] + prices[i-1] <= dp[arr[r-1] - 1] + prices[arr[r-1]-1]:
                r -= 1
            arr[r] = i
            r += 1
            ed = (i + 1) // 2
            while l < r and arr[l] < ed:
                l += 1
            dp[i] = dp[arr[l]-1] + prices[arr[l]-1]
        return dp[n]
            