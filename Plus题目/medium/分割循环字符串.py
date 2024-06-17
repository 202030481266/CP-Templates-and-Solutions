# 主要是总字符串长度是小于1000，暴力循环对比即可
class Solution:
    def splitLoopedString(self, strs: List[str]) -> str:
        strs = [s[::-1] if s[::-1] > s else s for s in strs]
        ans = ''.join(strs)
        for i, s in enumerate(strs):
            other = ''.join(strs[i + 1:]) + ''.join(strs[: i])
            for j, _ in enumerate(s):
                head = s[j:]
                tail = s[: j]
                cur = head + other + tail
                ans = max(ans, cur)
                cur = tail[::-1] + other + head[::-1]
                ans = max(ans, cur)
        return ans