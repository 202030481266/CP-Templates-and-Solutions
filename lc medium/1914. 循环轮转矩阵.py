from typing import List

class Solution:
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        n, m = len(grid), len(grid[0])

        def rotate(arr):
            N = len(arr)
            vis = [0] * N
            i = 0
            while i < N:
                if not vis[i]: 
                    cur = arr[i]
                    p = (i + k) % N
                    while not vis[p]:
                        vis[p] = True
                        cur, arr[p] = arr[p], cur
                        p = (p + k) % N
                i += 1
            return arr
    
        def get_arr(x1, y1, x2, y2):
            arr = []
            for i in range(x1, x2):
                arr.append(grid[i][y1])
            for i in range(y1, y2):
                arr.append(grid[x2][i])
            for i in range(x2, x1, -1):
                arr.append(grid[i][y2])
            for i in range(y2, y1, -1):
                arr.append(grid[x1][i])
            return arr
        
        def modify_grid(arr, x1, y1, x2, y2):
            p = 0
            for i in range(x1, x2):
                grid[i][y1] = arr[p]
                p += 1
            for i in range(y1, y2):
                grid[x2][i] = arr[p]
                p += 1
            for i in range(x2, x1, -1):
                grid[i][y2] = arr[p]
                p += 1
            for i in range(y2, y1, -1):
                grid[x1][i] = arr[p]
                p += 1
        
        t = min(n, m) // 2
        for i in range(t):
            lx, ly = n - i*2, m - i*2
            arr = get_arr(i, i, i + lx - 1, i + ly - 1)
            arr = rotate(arr)
            modify_grid(arr, i, i, i + lx - 1, i + ly - 1)
        
        return grid