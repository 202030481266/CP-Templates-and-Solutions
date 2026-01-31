class Solution:
    def minArrivalsToDiscard(self, arrivals: List[int], w: int, m: int) -> int:
        cnt = defaultdict(int)
        l = 0
        ans = 0
        vis = [0] * len(arrivals)
        for i, v in enumerate(arrivals):
            while i - l + 1 > w:
                if vis[l]:
                    cnt[arrivals[l]] -= 1
                l += 1
            if cnt[v] + 1 <= m:
                vis[i] = 1
                cnt[v] += 1
            else:
                ans += 1
        return ans