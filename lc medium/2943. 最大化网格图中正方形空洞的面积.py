from typing import List

class Solution:
    def maximizeSquareHoleArea(self, n: int, m: int, hBars: List[int], vBars: List[int]) -> int:
        hBars.sort()
        vBars.sort()
        def cal(arr) -> int:
            cur, pre = 0, 1
            x = 1
            for i in range(1,len(hBars)):
                cur = 1
                if hBars[i] == hBars[i-1] + 1:
                    cur += pre
                if cur > x:
                    x = cur
                pre = cur
            return x
        return min(cal(hBars), cal(vBars)) + 1