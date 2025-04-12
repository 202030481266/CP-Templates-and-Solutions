from typing import List

class Solution:
    def minimumLines(self, stockPrices: List[List[int]]) -> int:
        n = len(stockPrices)
        i = 0
        ans = 0
        stockPrices.sort()
        while i + 1 < n:
            j = i + 1
            delta_y = stockPrices[j][1] - stockPrices[i][1]
            delta_x = stockPrices[j][0] - stockPrices[i][0]
            while j + 1 < n and (stockPrices[j + 1][1] - stockPrices[j][1]) * delta_x == delta_y * (stockPrices[j + 1][0] - stockPrices[j][0]):
                j += 1
            ans += 1
            i = j
        return ans
        