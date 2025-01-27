from typing import List

class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        ans = 0
        # [n-limit, n]
        # [0, 2*limit]
        right = 2*limit if n > 2*limit else n
        left = n-limit if n > limit else 0
        if left > right: 
            return 0
        if right <= limit:
            # [left+1, right+1]
            return (right+left+2)*(right-left+1)//2
        if left >= limit:
            # [2*limit-left+1, 2*limit-right+1]
            return (4*limit-left-right+2)*(right-left+1)//2
        # [left, limit], [limit+1, right] 
        return (limit+left+2)*(limit-left+1)//2 + \
            (3*limit-right+1)*(right-limit)//2