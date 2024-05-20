from math import gcd

class Solution:
    def mirrorReflection(self, p: int, q: int) -> int:
        # 拆分成垂直方向和水平方向的往返运动，那么问题等价于找到最小的整数k使得kq是p的倍数
        g = gcd(p,q)
        # kq = p * q // g, k = p * q // g // q = p // g, kq / p = p * q // g // p = q // g
        p //= g
        q //= g
        p %= 2
        q %= 2
        return q if p == 1 else 2
