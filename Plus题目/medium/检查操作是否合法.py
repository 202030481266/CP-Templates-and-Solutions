dirs = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]

class Solution:
    def checkMove(self, board, rMove, cMove, color):
        n, m = len(board), len(board[0])
        board[rMove][cMove] = color
        # 检查八个方向
        target = 'W' if color == 'B' else 'B'
        for d in dirs:
            length = 1
            x, y = rMove + d[0], cMove + d[1]
            while 0 <= x < n and 0 <= y < m and board[x][y] == target:
                length += 1
                x += d[0]
                y += d[1]
            if 0 <= x < n and 0 <= y < m and board[x][y] == color and length > 1:
                return True
        return False