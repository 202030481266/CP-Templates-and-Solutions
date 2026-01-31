from typing import List

class Solution:
    def matrixSumQueries(self, n: int, queries: List[List[int]]) -> int:
        row,col = n,n
        ans = 0 
        row_vis = [0] * n
        col_vis = [0] * n
        for t,c,x in reversed(queries):
            if t:
                if not col_vis[c]:
                    ans += x*row
                    col -= 1
                    col_vis[c] = 1
            else:
                if not row_vis[c]:
                    ans += x*col
                    row -= 1
                    row_vis[c] = 1
        return ans
                
        