from typing import List

inf = 0x3f3f3f3f3f3f3f3f

class Solution:
    def minCost(self, n: int, cost: List[List[int]]) -> int:
        dp = [[[inf for _ in range(3)] for _ in range(3)] for _ in range(n//2)]
        for i in range(3):
            for j in range(3):
                if i != j:
                    dp[0][i][j] = cost[0][i] + cost[n-1][j]
        for i in range(1, n//2):
            for a in range(3):
                for b in range(3):
                    if a != b:
                        for x in range(3):
                            if x != a:
                                for y in range(3):
                                    if y != b:
                                        dp[i][a][b] = min(dp[i][a][b], dp[i-1][x][y] + cost[i][a] + cost[n-i-1][b])
        return min(dp[n//2-1][i][j] for i in range(3) for j in range(3) if i != j)