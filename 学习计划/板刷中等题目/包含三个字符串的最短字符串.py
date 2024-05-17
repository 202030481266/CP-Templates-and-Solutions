class Solution:
    def minimumString(self, a: str, b: str, c: str) -> str:
        # 最大前后缀拼接
        # abc, acb, bac, bca, cab, cba，做多尝试8次
        ans = a + b + c
        def pin(x, y) -> str:
            if y in x:
                return x
            for i in range(len(y), 0, -1):
                if y[:i] == x[-i:]:
                    return x + y[i:]
            return x + y
        def cal(a, b, c):
            nonlocal ans
            cur = pin(a, b)
            cur = pin(cur, c)
            if len(cur) < len(ans) or len(cur) == len(ans) and cur < ans:
                ans = cur
        cal(a,b,c)
        cal(a,c,b)
        cal(b,a,c)
        cal(b,c,a)
        cal(c,a,b)
        cal(c,b,a)
        return ans