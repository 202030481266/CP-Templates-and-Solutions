from collections import defaultdict

class Solution:
    def isReflected(self, points: List[List[int]]) -> bool:
        p = list(set(map(tuple, points)))
        p.sort()
        xs = defaultdict(list)
        for x, y in p:
            xs[y].append(x)
        mid = None
        for y,s in xs.items():
            i, j = 0, len(s)-1
            if mid is None:
                mid = s[i] + s[j]
            while i <= j:
                if s[i] + s[j] != mid:
                    return False
                i += 1
                j -= 1
        return True



        