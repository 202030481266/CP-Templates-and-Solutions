from collections import defaultdict
class Solution:
    def numberOfSpecialSubstrings(self, s: str) -> int:
        n = len(s)
        # 考虑一个事实，就是当长度越长，特殊子串的概率越小
        l, ans = 0, 0
        cnt = defaultdict(int)
        for i,v in enumerate(s):
            cnt[v] += 1
            while cnt[v] > 1:
                cnt[s[l]] -= 1
                l += 1
            if i >= l:
                ans += i-l+1
        return ans