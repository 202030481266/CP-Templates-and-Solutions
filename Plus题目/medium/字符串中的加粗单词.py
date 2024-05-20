class Solution:
    def boldWords(self, words: List[str], s: str) -> str:
        # 暴力匹配算法
        n = len(s)
        bold = [False] * n
        for w in words:
            m = len(w)
            for i in range(n - m + 1):
                if s[i:i + m] == w:
                    for j in range(i, i + m):
                        bold[j] = True
        ans = ""
        i = 0
        while i < n:
            if bold[i]:
                j = i
                while j < n and bold[j]:
                    j += 1
                # [i, j)
                ans += "<b>" + s[i:j] + "</b>"
                i = j
            else:
                ans += s[i]
                i += 1
        return ans
        

