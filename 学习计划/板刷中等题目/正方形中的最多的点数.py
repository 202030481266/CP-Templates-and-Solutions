inf = 0x3f3f3f3f
class Solution:
    def maxPointsInsideSquare(self, points: List[List[int]], s: str) -> int:
        # O(nlogn) is simple
        # O(n) is very tricky，the most iz mportant thing is define a metric that
        # if a square contains a point(x,y), that its distance >= max(abs(x),abs(y))
        min1 = [inf] * 26
        min2 = inf
        n = len(s)
        for i in range(n):
            x, y = points[i]
            j = ord(s[i]) - ord('a')
            d = max(abs(x), abs(y))
            if d < min1[j]:
                min2 = min(min2, min1[j])
                min1[j] = d
            elif d < min2:
                min2 = d
        return sum(d < min2 for d in min1)