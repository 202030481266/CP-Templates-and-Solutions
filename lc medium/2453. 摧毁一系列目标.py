from typing import List
from collections import defaultdict

class Solution:
    def destroyTargets(self, nums: List[int], space: int) -> int:
        cnt = defaultdict(int)
        for v in nums:
            cnt[v % space] += 1
        mx = max(cnt.values())
        ks = {v for v in cnt if cnt[v] == mx}
        ans = 10**9
        for v in nums:
            if v % space in ks and v < ans:
                ans = v
        return ans