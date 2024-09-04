class Solution:
    def maxPrice(self, items: List[List[int]], capacity: int) -> float:
        items.sort(key=lambda x: x[0]/x[1], reverse=True)
        ans = 0
        for price,weight in items:
            if capacity == 0:
                break
            if capacity >= weight:
                ans += price
                capacity -= weight
            else:
                ans += price/weight*capacity
                capacity = 0
        return -1 if capacity else ans
