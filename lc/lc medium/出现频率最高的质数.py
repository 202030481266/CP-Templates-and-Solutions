from typing import List
from collections import defaultdict

dirs = [(0,1),(1,0),(0,-1),(-1,0),(1,1),(-1,-1),(1,-1),(-1,1)]

class Solution:
    def mostFrequentPrime(self, mat: List[List[int]]) -> int:
        n,m = len(mat),len(mat[0])
        cnt = defaultdict(int)
        
        def check_prime(x):
            if x < 2:
                return False
            for i in range(2,int(x**0.5)+1):
                if x % i == 0:
                    return False
            return True
        
        for i in range(n):
            for j in range(m):
                for dx,dy in dirs:
                    x,y = i, j
                    cur = mat[x][y]
                    while 0 <= x+dx < n and 0 <= y+dy < m:
                        x += dx
                        y += dy
                        cur = cur * 10 + mat[x][y]
                        if check_prime(cur):
                            cnt[cur] += 1
        if not cnt.values():
            return -1
        max_cnt = max(cnt.values())
        ans = -1
        for key in cnt:
            if cnt[key] == max_cnt:
                ans = max(ans,key)
        return ans