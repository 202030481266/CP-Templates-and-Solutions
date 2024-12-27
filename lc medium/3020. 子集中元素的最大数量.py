from typing import List
from collections import defaultdict

class Solution:
    def maximumLength(self, nums: List[int]) -> int:
        cnt = defaultdict(int)
        for v in nums:
            cnt[v] += 1
        ans = cnt[1]-1 if cnt[1]%2 == 0 else cnt[1]
        for v in nums:
            if v == 1:
                continue
            cur = v
            res = 1
            while cnt[cur] > 1 and cnt[cur*cur] > 0:
                res += 1
                cur *= cur
            ans = max(ans, res*2-1)
        return ans

                