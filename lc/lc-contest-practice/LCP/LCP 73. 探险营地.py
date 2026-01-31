from typing import List

class Solution:
    def adventureCamp(self, expeditions: List[str]) -> int:
        cnt = set()
        def f(index):
            nonlocal cnt
            words = expeditions[index].split('->')
            res = 0
            for w in words:
                if w and w not in cnt:
                    res += 1
                    cnt.add(w)
            return res
        f(0)
        mx = 0
        ans = -1
        for i in range(1, len(expeditions)):
            res = f(i)
            if res > mx:
                ans = i
                mx = res
        return ans
