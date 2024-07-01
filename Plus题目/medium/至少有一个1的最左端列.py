# """
# This is BinaryMatrix's API interface.
# You should not implement it, or speculate about its implementation
# """
#class BinaryMatrix(object):
#    def get(self, row: int, col: int) -> int:
#    def dimensions(self) -> list[]:

# 强烈推荐开区间的二分写法
class Solution:
    def leftMostColumnWithOne(self, binaryMatrix: 'BinaryMatrix') -> int:
        n, m = binaryMatrix.dimensions()
        # find the leftmost column with 1
        l = -1
        r = m
        res = False
        while l+1 < r:
            mid = (l+r) // 2
            flag = False
            for i in range(n):
                if binaryMatrix.get(i, mid) == 1:
                    flag = True
                    break
            if flag:
                res = True 
                r = mid
            else:
                l = mid
        return r if res else -1