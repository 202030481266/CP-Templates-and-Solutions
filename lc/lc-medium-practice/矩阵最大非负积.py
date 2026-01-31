class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        # 2 * n * m
        inf = 4 ** 30
        mod = 10 ** 9 + 7
        dp = [[[-inf,inf] for _ in range(m+1)] for _ in range(n+1)]
        dp[0][1][0] = dp[0][1][1] = 1
        for i in range(1,n+1):
            for j in range(1,m+1):
                dp[i][j][0] = -inf
                dp[i][j][1] = inf
                if grid[i-1][j-1] == 0:
                    dp[i][j][0] = 0
                    dp[i][j][1] = 0
                elif grid[i-1][j-1] < 0:
                    if dp[i-1][j][1] <= 0:
                        dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][1] * grid[i-1][j-1]) 
                    if dp[i][j-1][1] <= 0:
                        dp[i][j][0] = max(dp[i][j][0], dp[i][j-1][1] * grid[i-1][j-1])
                    if dp[i-1][j][0] >= 0:
                        dp[i][j][1] = min(dp[i][j][1], dp[i-1][j][0] * grid[i-1][j-1])
                    if dp[i][j-1][0] >= 0:
                        dp[i][j][1] = min(dp[i][j][1], dp[i][j-1][0] * grid[i-1][j-1])
                else:
                    if dp[i-1][j][0] >= 0:
                        dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][0] * grid[i-1][j-1])
                    if dp[i][j-1][0] >= 0:
                        dp[i][j][0] = max(dp[i][j][0], dp[i][j-1][0] * grid[i-1][j-1])
                    if dp[i-1][j][1] <= 0:
                        dp[i][j][1] = min(dp[i][j][1], dp[i-1][j][1] * grid[i-1][j-1])
                    if dp[i][j-1][1] <= 0:
                        dp[i][j][1] = min(dp[i][j][1], dp[i][j-1][1] * grid[i-1][j-1])
        return dp[n][m][0] % mod if dp[n][m][0] >= 0 else -1

        