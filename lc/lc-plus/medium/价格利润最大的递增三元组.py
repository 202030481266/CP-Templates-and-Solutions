class Solution:
    def maxProfit(self, prices: List[int], profits: List[int]) -> int:
        n = len(prices)
        mx = [0] * n
        for i in range(n):
            for j in range(i):
                if prices[j] < prices[i]: 
                    mx[i] = max(mx[i], profits[i] + profits[j])
        ans = -1
        for i in range(n):
            for j in range(i):
                if prices[j] < prices[i] and mx[j] > 0: 
                    ans = max(ans, profits[i] + mx[j])
        return ans