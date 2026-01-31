from typing import List
from collections import defaultdict

class Solution:
    def getDistances(self, arr: List[int]) -> List[int]:
        pos = defaultdict(list)
        for i, v in enumerate(arr):
            pos[v].append(i)
        ans = [0] * len(arr)
        for k, v in pos.items():
            n = len(v)
            s = [0] * (n+1)
            for i in range(n):
                s[i + 1] = s[i] + v[i]
            for i, x in enumerate(v, 1):
                ans[x] = i * x - s[i] + (s[n] - s[i]) - (n - i) * x
        return ans