class Solution:
    def kthPalindrome(self, queries: List[int], intLength: int) -> List[int]:
        ans = []
        if intLength % 2 == 0:
            upper = 10 ** (intLength // 2) - 1
            lower = 10 ** (intLength // 2 - 1)
            for q in queries:
                # [10,99], [100,999],[1000,9999]
                if q > upper - lower + 1:
                    ans.append(-1)
                else:
                    val = lower + q - 1
                    ans.append(int(str(val) + str(val)[::-1]))
        else:
            pre = intLength // 2
            # pre + num + rev(pre), total is 10 * pre 种数字, pre > 0
            upper, lower = (0, 0) if pre == 0 else (10 ** (pre) - 1, 10 ** (pre - 1))
            for q in queries:
                if q > 10 * (upper - lower + 1): 
                    ans.append(-1)
                elif pre == 0:
                    if q >= 10: # 不包括0
                        ans.append(-1)
                    else:
                        ans.append(q)
                else:
                    q -= 1
                    d, r = q // 10, q % 10 # 每一个pre都有10个搭配, 10, 11, 12, 13....19
                    val = lower + d 
                    ans.append(int(str(val) + str(r) + str(val)[::-1]))
        return ans

                