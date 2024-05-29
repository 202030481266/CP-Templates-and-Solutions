# Definition of commonBits API.
# def commonBits(num: int) -> int:

class Solution:
    def findNumber(self) -> int:
        ans = 0
        # 计算前30位中值相同的位数
        tot = 30-commonBits(0)
        for i in range(30):
            cur = 30-commonBits(1<<i)
            # 如果这个位数是1，那么必然将会导致不同的位数减少
            if cur==tot-1:
                ans += 1<<i
            commonBits(1<<i) # 回复
        return ans
            
        