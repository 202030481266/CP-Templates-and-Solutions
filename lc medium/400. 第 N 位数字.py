class Solution:
    def findKthNumber(self, n: int) -> int:
        # 1 ~ 9, 9
        # 10 ~ 99, 90
        # 100 ~ 999, 900
        s = 0
        k = 0
        while s < n:
            k += 1
            s += 9 * (10 ** (k-1)) * k
        s -= 9 * (10 ** (k-1)) * k
        n -= s
        num = 10 ** (k-1) + (n-1) // k if n % k == 0 else 10 ** (k-1) + n // k 
        r = (n-1) % k
        return int(str(num)[r])