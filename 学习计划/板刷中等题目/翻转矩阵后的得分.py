class Solution:
    def matrixScore(self, grid: List[List[int]]) -> int:
        # 不是DP，而是贪心
        # 使得第一列全部为1有两种方法: 将所有的1翻转0 + 翻转列， 对所有的0行翻转
        n, m = len(grid), len(grid[0])
        r1, r2 = 0, 0
        for col in range(1,m):
            cnt = 0
            for row in range(n):
                cnt += (grid[row][0] ^ grid[row][col])
            r1 += max(cnt, n-cnt) * (1 << (m-col-1))    
        for col in range(1,m):
            cnt = 0
            for row in range(n):
                cnt += (1 - grid[row][0] ^ grid[row][col])
            r2 += max(cnt, n-cnt) * (1 << (m-col-1))
        return max(r1, r2) + n * (1<<(m-1))