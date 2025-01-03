from typing import List

class Solution:
    def largestArea(self, grid: List[str]) -> int:
        flag = False
        cnt = 0
        n, m = len(grid), len(grid[0])
        vis = [[0] * m for _ in range(n)]

        def dfs(x, y, num):
            nonlocal flag, cnt
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nx, ny = x + dx, y + dy
                if nx < 0 or ny < 0 or nx >= n or ny >= m or grid[nx][ny] == '0':
                    flag = True
                if nx >= 0 and ny >= 0 and nx < n and ny < m and grid[nx][ny] != '0':
                    if not vis[nx][ny] and grid[nx][ny] == num:
                        vis[nx][ny] = 1
                        cnt += 1
                        dfs(nx, ny, num)
        ans = 0
        for i in range(n):
            for j in range(m):
                if not vis[i][j] and grid[i][j] != '0':
                    flag = False
                    cnt = 1
                    vis[i][j] = True
                    dfs(i, j, grid[i][j])
                    if not flag:
                        ans = max(ans, cnt)
        return ans