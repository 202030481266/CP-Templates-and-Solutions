class Solution:
    def countSteppingNumbers(self, low: int, high: int) -> List[int]:
        lo, hi = str(low), str(high)
        ans = []
        cur = []
        n = len(hi)
        diff = n - len(lo)
        def dfs(p, limit_low, limit_high):
            nonlocal ans, cur, n, diff, lo, hi
            if p == n:
                ans.append(int(''.join(cur)))   
                return
            l = int(lo[p-diff]) if limit_low and p >= diff else 0
            h = int(hi[p]) if limit_high else 9
            d = l # 枚举的数位
            if limit_low and p < diff: # 什么也没有填写
                dfs(p + 1, True, False)
                d += 1 # 说明枚举的数位一定是大于等于1的
            if len(cur):
                pre = int(cur[-1])
                for i in [pre - 1, pre + 1]:
                    if d <= i <= h:
                        cur.append(str(i))
                        dfs(p + 1, limit_low and i == l, limit_high and i == h)
                        cur.pop()
            else:
                for i in range(d, h + 1):
                    cur.append(str(i))
                    dfs(p + 1, limit_low and i == l, limit_high and i == h)
                    cur.pop()
        dfs(0, True, True)
        return ans
