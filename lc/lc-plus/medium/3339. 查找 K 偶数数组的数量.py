mod = 10**9 + 7
class Solution:
    def countOfArrays(self, n: int, m: int, k: int) -> int:
        dp = [[[0] * 2 for i in range(k+1)] for _ in range(n)] # n * (k+1) * 2
        odd = (m+1)//2
        even = m//2
        dp[0][0][0] = even
        dp[0][0][1] = odd
        for i in range(1,n):
            for j in range(k+1):
                # odd
                dp[i][j][1] = (dp[i-1][j][0] + dp[i-1][j][1]) % mod * odd % mod
                # even
                dp[i][j][0] += dp[i-1][j][1] * even % mod
                if j > 0:
                    dp[i][j][0] += dp[i-1][j-1][0] * even % mod
        return (dp[n-1][k][0] + dp[n-1][k][1]) % mod
        
        