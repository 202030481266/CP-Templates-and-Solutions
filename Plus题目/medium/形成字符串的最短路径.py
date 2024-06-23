# dp
class Solution:
    def shortestWay(self, source: str, target: str) -> int:
        n,m = len(source),len(target)
        inf = 0x3f3f3f3f
        dp = [inf] * (m+1)
        dp[0] = 0
        for i in range(1,m+1):
            j = i-1
            p = n-1
            while j >= 0 and p >= 0:
                if target[j] == source[p]:
                    dp[i] = min(dp[i], dp[j]+1)
                    j -= 1
                p -= 1
        return -1 if dp[m] == inf else dp[m]

# 贪心
class Solution:
    def shortestWay(self, source: str, target: str) -> int:
        n,m = len(source),len(target)
        # x + y + z， 如果 x + y 本来就可以是一个子序列，那么就有 (x+y) + z
        # x + y + z， 如果 y + z也可以是一个子序列，那么就有 (x+y+z) 本身就是一个子序列
        cnt = set(source)
        for c in target:
            if c not in cnt:
                return -1
        i = 0
        ans = 0
        while i < m:
            j = 0
            ans += 1
            while i < m and j < n:
                if source[j] == target[i]:
                    i += 1
                j += 1
        return ans

# 严格意义来说， dp 和 贪心复杂度相同，但是贪心跑的快很多，leetcode上的数据分布有点问题
        
