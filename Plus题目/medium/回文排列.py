from collections import defaultdict

class Solution:
    def generatePalindromes(self, s: str) -> List[str]:
        cnt = defaultdict(int)
        for c in s:
            cnt[c] += 1
        r = 0
        mid = ""
        for k,v in cnt.items():
            if v % 2 > 0:
                r += 1
                mid = k
            cnt[k] //= 2
            if r > 1:
                return []
        n = len(s)
        ans = []
        cur = ""
        def dfs(p):
            nonlocal ans,n,cur
            if p == n//2:
                if r > 0:
                    ans.append(cur + mid + cur[::-1])
                else:
                    ans.append(cur + cur[::-1])
                return     
            for k in cnt.keys():
                if cnt[k] > 0:
                    cur += k
                    cnt[k] -= 1
                    dfs(p+1)
                    cnt[k] += 1
                    cur = cur[:-1]
        dfs(0)
        return ans
            