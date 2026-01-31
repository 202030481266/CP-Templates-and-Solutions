from collections import defaultdict

class Solution:
    def wordPatternMatch(self, pattern: str, s: str) -> bool:
        # dfs
        # 剪枝：字符的长度限制性
        cnt = defaultdict(int)
        n,m = len(s),len(pattern)
        for c in pattern:
            cnt[c] += 1
        # 对于每一个状态而言，都有一个最大的可选择长度和最小可选择长度
        cur = dict()
        use = set()
        unknow = m
        left = n
        def dfs(p,q) -> bool:
            nonlocal cur,use,n,m,cnt,unknow,left
            if p >= n or q >= m:
                if p == n and q == m:
                    return True
                return False
            c = pattern[q]
            if cur.get(c) is None:
                # 没有对应的映射单词
                mn = max(1,left//unknow)
                mx = (left-(unknow-cnt[c]))//cnt[c]+1
                for i in range(mn,mx+1):
                    tmp = s[p:p+i]
                    if tmp in use:
                        continue
                    cur[c] = tmp
                    use.add(tmp)
                    left -= i*cnt[c]
                    unknow -= cnt[c]
                    if dfs(p+i,q+1):
                        return True
                    # 回溯
                    left += i*cnt[c]
                    unknow += cnt[c]
                    use.remove(tmp)
                    cur[c] = None
                return False
            else:
                # 有对应的映射单词
                tmp = cur[c]
                if p+len(tmp) <= n and s[p:p+len(tmp)] == tmp:
                    return dfs(p+len(tmp),q+1)
                return False
        return dfs(0,0)



            
            
