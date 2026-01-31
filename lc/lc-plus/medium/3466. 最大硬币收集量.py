# 阅读理解题目
class Solution:
    def maxCoins(self, lane1: List[int], lane2: List[int]) -> int:
        n = len(lane1)
        dp = [[-0x3f3f3f3f] * 3 for _ in range(n+1)]
        dp[0][2] = 0
        for i in range(1,n+1):
            dp[i][2] = max(dp[i-1][2], 0) + lane1[i-1]
        for i in range(1, n+1):
            if i > 0:
                dp[i][1] = max(dp[i-1][1], dp[i-1][2]) + lane2[i-1]
            dp[i][1] = max(dp[i][1], lane2[i-1]) # 直接从上面下来并且立即切换
        for i in range(2,n+1):
            dp[i][0] = max(dp[i-1][1], dp[i-1][0]) + lane1[i-1]
        ans = -0x3f3f3f3f
        for i in range(1,n+1):
            t = max(dp[i][0], dp[i][1], dp[i][2])
            if ans < t:
                ans = t
        return ans
