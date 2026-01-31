class Solution:
    def maxScore(self, a: List[int], b: List[int]) -> int:
        n = len(b)
        dp = [float('-inf')] * 5
        dp[0] = 0
        for i in range(n):
            for k in range(4, 0, -1):
                dp[k] = max(dp[k], dp[k - 1] + a[k - 1] * b[i])
        return dp[4]