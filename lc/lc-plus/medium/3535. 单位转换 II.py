from typing import List

mod = 1000000007


def quick_pow(a, b):
    res = 1
    while b:
        if b & 1:
            res = res * a % mod
        a = a * a % mod
        b //= 2
    return res


def modInverse_fermat(a, p):
    """
    使用费马小定理计算 a 关于质数 p 的模逆元。

    Args:
      a: 目标整数。
      p: 质数模数。

    Returns:
      a 关于模 p 的逆元 (一个 1 到 p-1 之间的整数)。
      如果 p 不是质数或 a 是 p 的倍数，结果未定义（或可能出错）。
      如果 a 是 p 的倍数 (a % p == 0)，则逆元不存在，返回 None。
    Raises:
      ValueError: 如果 p 不是大于 1 的整数。
    """
    if not isinstance(p, int) or p <= 1:
        raise ValueError("模数 p 必须是大于 1 的整数。")
    a = a % p
    if a == 0:
        print(f"错误：{a // p * p} (即 0 mod {p}) 没有模 {p} 的逆元。")
        return None
    inverse = quick_pow(a, mod - 2)
    return inverse


class Solution:
    def gcd(self, a, b):
        while b:
            a, b = b, a % b
        return a

    def queryConversions(
        self, conversions: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        n = len(conversions) + 1
        graph = [[] for _ in range(n)]
        for u, v, w in conversions:
            graph[u].append((v, w))
        q = [0]
        arr = [1] * n
        while q:
            tmp = []
            for u in q:
                for v, w in graph[u]:
                    arr[v] = arr[u] * w % mod
                    tmp.append(v)
            q = tmp
        ans = []
        for u, v in queries:
            x, y = arr[u], arr[v]
            g = self.gcd(x, y)
            x //= g
            y //= g
            if y % x == 0:
                ans.append(y // x)
            else:
                ans.append(y * modInverse_fermat(x, mod) % mod)
        return ans
