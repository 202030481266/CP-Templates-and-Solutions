from typing import List

dirs = ((0, 1), (1, 0), (0, -1), (-1, 0))

# 此题细节非常多，边界条件处理很复杂

class Solution:
    def spiralMatrixIII(self, n: int, m: int, rStart: int, cStart: int) -> List[List[int]]:
        tot = 0
        vis = [[0] * m for _ in range(n)]
        x, y = rStart, cStart
        cur = 0
        ans = []
        while True:
            vis[x][y] = 1
            tot += 1
            ans.append([x, y])
            if tot == n * m:
                break
            nx, ny = x + dirs[cur][0], y + dirs[cur][1]
            if nx >= 0 and ny >= 0 and nx < n and ny < m and not vis[nx][ny]:
                x, y = nx, ny
            else:
                while vis[x][y]:
                    cur = (cur + 1) % 4
                    nx, ny = x + dirs[cur][0], y + dirs[cur][1]
                    while nx >= 0 and ny >= 0 and nx < n and ny < m and vis[x][y]:
                        x, y = nx, ny
                        nx, ny = x + dirs[cur][0], y + dirs[cur][1]
            nxt = (cur + 1) % 4
            nxt_x, nxt_y = x + dirs[nxt][0], y + dirs[nxt][1]
            if nxt_x < 0 or nxt_y < 0 or nxt_x >= n or nxt_y >= m or not vis[nxt_x][nxt_y]:
                cur = (cur + 1) % 4
        return ans 
                