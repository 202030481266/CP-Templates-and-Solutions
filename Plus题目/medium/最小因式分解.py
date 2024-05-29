mx = (1<<31)-1
class Solution:
    def smallestFactorization(self, num: int) -> int:
        if num == 1: # 特判
            return 1
        a = []
        change = True
        while num > 1 and change:
            pre = num
            for i in range(9,0,-1):
                if num % i == 0:
                    a.append(i)
                    num //= i
                    break
            change = False if num == pre else True
        if not change and num > 1: # 说明由大于9的质数乘积构成
            return 0
        a.sort()
        n,ans = len(a),0
        for i in range(n):
            ans += 10**(n-1-i) * a[i]
        return 0 if ans > mx else ans