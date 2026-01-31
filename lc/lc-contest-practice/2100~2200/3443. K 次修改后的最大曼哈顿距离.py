from typing import List

# 枚举四个象限的最大点，贪心修改

class Solution:
    def maxDistance(self, s: str, k: int) -> int:
        def f(ss):
            x, y = 0, 0
            res = 0
            for c in ss:
                if c == 'N':
                    y += 1
                elif c == 'W':
                    x -= 1
                elif c == 'E':
                    x += 1
                else:
                    y -= 1
                res = max(res, abs(x) + abs(y))
            return res

        ans = 0
        for id1, c1 in enumerate('NS'):
            for id2, c2 in enumerate('WE'):
                b = list(s)  # 转换为列表
                i = 0
                c = k
                while i < len(b) and c:
                    if b[i] == c1:
                        b[i] = 'NS'[id1 ^ 1]
                        c -= 1
                    elif b[i] == c2:
                        b[i] = 'WE'[id2 ^ 1]
                        c -= 1
                    i += 1
                ans = max(ans, f("".join(b)))  # 重新转换回字符串
        return ans
