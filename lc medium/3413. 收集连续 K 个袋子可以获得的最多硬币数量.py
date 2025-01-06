from typing import List

# 可以证明出来，滑动窗口的一个端点必然是区间的某一个端点

class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        n = len(coins)
        coins.sort(key=lambda x: x[0])
        pre = [0] * (n + 1)
        for i in range(n):
            pre[i + 1] = pre[i] + coins[i][2]*(coins[i][1] - coins[i][0] + 1)
        r = 0
        ans = 0
        for i in range(n):
            right = coins[i][0] + k - 1
            while r < n and coins[r][1] <= right:
                r += 1
            # [i, r)
            # res = pre[r-1] - pre[i-1]
            res = pre[r] - pre[i]
            if r < n and coins[r][0] <= right:
                res += (right - coins[r][0] + 1) * coins[r][2]
            ans = max(ans, res)
        l = 0
        for i in range(n):
            left = coins[i][1] - k + 1
            while coins[l][1] < left:
                l += 1
            # (l, i]
            # pre[i] - pre[l]
            res = pre[i+1] - pre[l+1]
            res += (coins[l][1] - max(left, coins[l][0]) + 1) * coins[l][2]
            ans = max(ans, res)
        return ans