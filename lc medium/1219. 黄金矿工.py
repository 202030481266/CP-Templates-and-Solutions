from typing import List

dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]

# NP问题， 哈密顿路径
# 搜索剪枝

class Solution:
    def getMaximumGold(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        s = 0
        for i in range(n):
            for j in range(m):
                s += grid[i][j]
        cur = 0
        ans = 0
        vis = [[0] * m for _ in range(n)]
        # s用来做最优性剪枝
        def dfs(x, y):
            nonlocal cur, ans, s
            if cur > ans:
                ans = cur
            for dx, dy in dirs:
                if 0 <= x + dx < n and 0 <= y + dy < m and grid[x + dx][y + dy] > 0 and not vis[x + dx][y + dy]:
                    # 剩下的 + 现在的 可能超越 ans
                    # 更加强大的剪枝 -> 从某个点出发所有能够到达的点的和 - 现在已经访问过的点的和
                    if s + cur > ans:
                        vis[x + dx][y + dy] = 1
                        cur += grid[x + dx][y + dy]
                        s -= grid[x + dx][y + dy]
                        dfs(x + dx, y + dy)
                        s += grid[x + dx][y + dy]
                        cur -= grid[x + dx][y + dy]
                        vis[x + dx][y + dy] = 0
        
        # 这里随机使用一点出发，实际上可以从全局最大值降序遍历
        for i in range(n):
            for j in range(m):
                if grid[i][j] > 0:
                    vis[i][j] = 1
                    cur += grid[i][j]
                    s -= grid[i][j]
                    dfs(i, j)
                    s += grid[i][j]
                    cur -= grid[i][j]
                    vis[i][j] = 0
        return ans
         