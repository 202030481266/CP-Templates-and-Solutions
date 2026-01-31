class Solution:
    def maximizeTheProfit(self, n: int, offers: List[List[int]]) -> int:
        # 选择一些区间，使得利润最大化
        # 贪心可以解决权重全为1的区间问题，但是这里需要使用动态规划
        mx = [0] * n
        dp = [0] * n
        p, m = 0, len(offers)
        offers.sort(key=lambda x: x[1])
        for i in range(n):
            while p < m and offers[p][1] < i:
                p += 1
            dp[i] = 0 if i == 0 else dp[i-1]
            while p < m and offers[p][1] == i: 
                ed = offers[p][0] - 1
                tmp = mx[ed] + offers[p][2] if ed >= 0 else offers[p][2]
                dp[i] = max(dp[i], tmp)
                p += 1
            mx[i] = dp[i] if i == 0 else max(mx[i-1], dp[i])
        return mx[n-1]
