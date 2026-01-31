from sortedcontainers import SortedList

class Solution:
    def countPairs(self, a: List[int], b: List[int]) -> int:
        # ai + aj > bi + bj
        # ai - bi > bj - aj
        # ai - bi > -(aj - bj)
        s = SortedList()
        ans = 0
        for i in range(len(a)):
            t = a[i] - b[i]
            ans += len(s) - s.bisect_right(-t)
            s.add(t)
        return ans