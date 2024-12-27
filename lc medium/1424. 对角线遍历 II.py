from typing import List

class Solution:
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        # x+y=val, val=0,1,2,3,4....
        res = [] 
        for i in range(len(nums)):
            for j in range(len(nums[i])):
                res.append((i+j,-i))
        res.sort()
        return [nums[-y][x+y] for x,y in res]