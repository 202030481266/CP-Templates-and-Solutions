from typing import List

class Solution:
    
    def minimumLines(self, points: List[List[int]]) -> int:
        n = len(points)
        valid = [True] * (1<<n)
        siz = [0] * (1<<n)
        for i in range(1,(1<<n)):
            p = []
            for j in range(n):
                if (i & (1<<j)):
                    p.append(j)
            siz[i] = len(p)
            if len(p) <= 2:
                continue
            v1 = [points[p[1]][0]-points[p[0]][0], points[p[1]][1]-points[p[0]][1]]
            for k in range(2, len(p)):
                v2 = [points[p[k]][0]-points[p[0]][0], points[p[k]][1]-points[p[0]][1]]
                if v1[0] * v2[1] - v1[1] * v2[0] != 0:
                    valid[i] = False
                    break
        # add search
        ans = 0x3f3f3f3f

        def dfs(s, cur_ans):
            nonlocal ans
            # find the maximum subset, this is can be search very quick
            if s == 0:
                ans = ans if ans < cur_ans else cur_ans
                return
            if cur_ans >= ans:
                return
            sub = s
            mx = 0
            candi = []
            while sub:
                if valid[sub]:
                    if mx < siz[sub]:
                        candi = [sub]
                        mx = siz[sub]
                    elif mx == siz[sub]:
                        candi.append(sub)
                sub = (sub-1) & s
            for c in candi:
                dfs(s ^ c, cur_ans + 1)
        
        dfs((1<<n)-1, 0)
        return ans

                    
            
            