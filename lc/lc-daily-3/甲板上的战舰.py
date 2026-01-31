class Solution:
    def countBattleships(self, board: List[List[str]]) -> int:
        n,m = len(board), len(board[0])
        vis = [[False]*m for i in range(n)]
        ans = 0
        for i in range(n):
            for j in range(m):
                if board[i][j] == '.' or vis[i][j]:
                    continue
                p = j
                while p < m and board[i][p] == 'X':
                    vis[i][p] = True
                    p += 1
                p = i
                while p < n and board[p][j] == 'X':
                    vis[p][j] = True
                    p += 1
                ans += 1
        return ans
                