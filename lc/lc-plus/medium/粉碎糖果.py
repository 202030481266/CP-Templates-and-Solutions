class Solution:
    def candyCrush(self, board: List[List[int]]) -> List[List[int]]:
        n,m = len(board),len(board[0])
        while True:
            crash = False
            vis = [[False]*m for _ in range(n)]
            for i in range(n):
                for j in range(m):
                    if board[i][j] == 0:
                        continue
                    # 横向拓展
                    p = j
                    while p < m and board[i][j] == board[i][p]:
                        p += 1
                    if p-j >= 3:
                        crash = True
                        for k in range(j,p):
                            vis[i][k] = True
                    # 纵向拓展
                    p = i
                    while p < n and board[p][j] == board[i][j]:
                        p += 1
                    if p-i >= 3:
                        crash = True
                        for k in range(i,p):
                            vis[k][j] = True
            if not crash:
                break
            for i in range(n):
                for j in range(m):
                    if vis[i][j]:
                        board[i][j] = 0
            for j in range(m):
                for i in range(n-1,-1,-1):
                    if board[i][j] > 0:
                        p = i
                        while p+1 < n and board[p+1][j] == 0:
                            board[p][j],board[p+1][j] = board[p+1][j],board[p][j]
                            p += 1
        return board
             