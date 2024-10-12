from typing import List

class Solution:
    def catchMaximumAmountofPeople(self, team: List[int], dist: int) -> int:
        ans = 0
        a = [i for i, v in enumerate(team) if v]
        p = 0
        if len(a) == 0:
            return 0
        for i, v in enumerate(team):
            if not v:
                while p < len(a) and a[p]+dist < i:
                    p += 1
                if p < len(a) and a[p]-dist <= i:
                    ans += 1
                    p += 1
        return ans
