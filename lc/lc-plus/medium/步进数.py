# 数位dp
class Solution:
    def countSteppingNumbers(self, low: int, high: int) -> List[int]:
        ans = 1 if low == 0 else 0
        low = max(low, 1)
        lo, hi = str(low-1), str(high)
        dp = [[-1] * 10 for _ in range(12)]
        def dfs(p, s, pre, is_limit, is_num):
            if p == len(s):
                return 1 if is_num else 0
            if not is_limit and is_num and dp[p][pre] != -1:
                return dp[p][pre]
            res = 0
            up = int(s[p]) if is_limit else 9 
            if not is_num:
                res += dfs(p + 1, s, pre, False, False)
                for i in range(1, up + 1):
                    res += dfs(p + 1, s, i, is_limit and i == up, True)
            else:
                for i in [pre - 1, pre + 1]:
                    if 0 <= i <= up:
                        res += dfs(p + 1, s, i, is_limit and i == up, True)
            if not is_limit and is_num:
                dp[p][pre] = res
            return res
        r1 = dfs(0, hi, 0, True, False) 
        dp = [[-1] * 10 for _ in range(12)]
        r2 = dfs(0, lo, 0, True, False)
        return r1 - r2 + ans
                

            