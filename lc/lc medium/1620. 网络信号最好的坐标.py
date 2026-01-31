from typing import List
import math

class Solution:
    def bestCoordinate(self, towers: List[List[int]], radius: int) -> List[int]:
        n = len(towers)
        N, M = 0, 0
        for x, y, _ in towers:
            if x + radius > N:
                N = x + radius
            if y + radius > M:
                M = y + radius
        mx = 0
        ansx, ansy = 0, 0
        for x in range(N + 1):
            for y in range(M + 1):
                res = 0
                for j in range(n):
                    dis = (x - towers[j][0]) ** 2 + (y - towers[j][1]) ** 2
                    if dis <= radius * radius:
                        res += math.floor(towers[j][2] / (1 + math.sqrt(dis)))
                if res > mx or res == mx and (x, y) < (ansx, ansy):
                    mx = res
                    ansx, ansy = x, y
        return [ansx, ansy]
                
