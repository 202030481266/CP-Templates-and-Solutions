from collections import defaultdict

class Solution:
    def shareCandies(self, candies: List[int], k: int) -> int:
        n = len(candies)
        cnt = defaultdict(int)
        tot = defaultdict(int)
        l = 0
        cur = 0
        for v in candies:
            tot[v] += 1
        ans = 0
        N = len(tot.keys())
        for i in range(n):
            cnt[candies[i]] += 1
            if cnt[candies[i]] == tot[candies[i]]:
                cur += 1
            while i-l+1 > k:
                if cnt[candies[l]] == tot[candies[l]]:
                    cur -= 1
                cnt[candies[l]] -= 1
                l += 1
            if i-l+1 == k and N-cur > ans:
                ans = N-cur
        return ans
