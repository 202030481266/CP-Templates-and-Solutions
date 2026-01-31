from typing import List

class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        n, m = len(grid), len(grid[0])
        ans = [-1] * m
        for i in range(m):
            j = i
            flag = True
            for r in range(n):
                if grid[r][j] == 1:
                    if j + 1 < m and grid[r][j + 1] == 1:
                        j += 1
                    else:
                        flag = False
                        break
                else:
                    if j - 1 >= 0 and grid[r][j - 1] == -1:
                        j -= 1
                    else:
                        flag = False
                        break
            if flag:
                ans[i] = j
        return ans
