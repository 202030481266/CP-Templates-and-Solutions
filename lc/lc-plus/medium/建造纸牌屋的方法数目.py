inf = 0x3f3f3f3f
class Solution:
    def houseOfCards(self, n: int) -> int:
        # f(x) = 2 + (x-1)*3 = 2 + 3x - 3 = 3x - 1
        @cache
        def dfs(x,b) -> int:
            if x == 0:
                return 1
            res = 0
            for i in range(1,b):
                if 3*i-1 > x:
                    break
                res += dfs(x-3*i+1,i)
            return res
        return dfs(n,inf)
