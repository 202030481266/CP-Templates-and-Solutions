class Solution:
    def longestLine(self, mat: List[List[int]]) -> int:
        n, m = len(mat), len(mat[0])
        vis = [[[0, 0, 0, 0] for j in range(m)] for i in range(n)]
        ans = 0
        for i in range(n):
            for j in range(m):
                if mat[i][j]:
                    if not vis[i][j][0]:
                        k = i          
                        while k < n and mat[k][j]:
                            vis[k][j][0] = 1
                            k += 1
                        ans = max(ans,k-i)
                    if not vis[i][j][1]:
                        k = j
                        while k < m and mat[i][k]:
                            vis[i][k][1] = 1
                            k += 1
                        ans = max(ans, k-j)
                    if not vis[i][j][2]:
                        k = 0
                        while i+k < n and j+k < m and mat[i+k][j+k]:
                            vis[i+k][j+k][2] = 1
                            k += 1
                        ans = max(ans, k)
                    if not vis[i][j][3]:
                        k = 0
                        while i+k < n and j-k >= 0 and mat[i+k][j-k]:
                            vis[i+k][j-k][3] = 1
                            k += 1
                        ans = max(ans, k)
        return ans