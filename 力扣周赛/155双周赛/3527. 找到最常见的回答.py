from typing import List
from collections import defaultdict

class Solution:
    def findCommonResponse(self, responses: List[List[str]]) -> str:
        ans = ""
        cnt = 0
        tot = defaultdict(int)
        for r in responses:
            vis = set()
            for s in r:
                if s not in vis:
                    tot[s] += 1
                    vis.add(s)
        for k, v in tot.items():
            if v > cnt or v == cnt and k < ans:
                cnt = v
                ans = k
        return ans
