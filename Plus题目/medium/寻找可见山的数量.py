from typing import List

class Solution:

    def visibleMountains(self, peaks: List[List[int]]) -> int:
        a = []
        for p in peaks:
            a.append([p[0]-p[1], p[0] + p[1]])
        a.sort()
        pre = -0x3f3f3f3f
        n = len(a)
        i = 0
        ans = 0
        while i < n:
            j = i+1
            while j < n and a[j][0] == a[i][0]:
                j += 1
            # [i,j)
            if j-i == 1:
                if a[i][1] > pre:
                    pre = a[i][1]
                    ans += 1
            else:
                if a[j-1][1] > pre:
                    if a[j-1][1] != a[j-2][1]:
                        ans += 1
                    pre = a[j-1][1]
            i = j
        return ans

            
