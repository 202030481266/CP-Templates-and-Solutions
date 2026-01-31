from collections import defaultdict

class Solution:
    def countPairs(self, deliciousness: List[int]) -> int:
        mod = 10**9 + 7
        ans = 0
        cnt = defaultdict(int)
        for v in deliciousness:
            msb = v.bit_length()
            for i in range(msb,22):
                ans = (ans + cnt[(1<<i) - v]) % mod
            if msb > 0 and 1<<(msb-1) == v:
                ans = (ans + cnt[0]) % mod
            cnt[v] += 1
        return ans
            