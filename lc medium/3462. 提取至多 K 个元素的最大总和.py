from typing import List 

class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        n, m = len(grid), len(grid[0])
        a = []
        for idx, row in enumerate(grid):
            row.sort()
            for i in range(m-1, m-limits[idx]-1, -1):
                a.append(row[i])
        a.sort()
        ans = 0
        for i in range(len(a)-1, len(a)-k-1, -1):
            ans += a[i]
        return ans
        