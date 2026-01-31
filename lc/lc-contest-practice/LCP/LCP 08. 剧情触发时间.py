from typing import List

class Solution:
    def getTriggerTime(self, increase: List[List[int]], requirements: List[List[int]]) -> List[int]:
        n = len(increase)
        a = [[0] * 3 for _ in range(n+1)]
        for i in range(n):
            for j in range(3):
                a[i+1][j] = a[i][j] + increase[i][j]

        def check(x, y, z, d):
            return a[d][0] >= x and a[d][1] >= y and a[d][2] >= z
        
        ans = []
        for x, y, z in requirements:
            l, r = -1, n+1
            while l + 1 < r:
                mid = (l + r) >> 1
                if check(x, y, z, mid):
                    r = mid
                else:
                    l = mid
            ans.append(r if r <= n else -1)
        return ans