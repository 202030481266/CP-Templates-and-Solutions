class Solution:
    def maximumDetonation(self, bombs: List[List[int]]) -> int:
        # 连环炸弹，实际上是图
        n = len(bombs)
        g = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i != j:
                    if (bombs[i][0] - bombs[j][0]) ** 2 + (bombs[i][1] - bombs[j][1]) ** 2 <= bombs[i][2] ** 2:
                        g[i][j] = 1
        vis = [False] * n
        cur = 0
        def dfs(u):
            nonlocal g, cur, vis
            vis[u] = True
            cur += 1
            for i in range(n):
                if g[u][i] and not vis[i]:
                    dfs(i)
        ans = 0
        for i in range(n):
            cur = 0
            vis = [False] * n
            dfs(i)
            if ans < cur:
                ans = cur
        return ans