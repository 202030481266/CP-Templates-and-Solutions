from typing import List

class Solution:
    def splitIntoFibonacci(self, num: str) -> List[int]:
        n = len(num)
        for i in range(0, n-2):
            if num[0] == '0' and i > 0: break
            for j in range(i+1,n-1):
                # [0,i], (i,j]
                if  num[i+1] == '0' and j > i+1: break
                a = int(num[:i+1])
                b = int(num[i+1:j+1])
                # check
                if a > 2**31-1 or b > 2**31-1:
                    break
                res = [i,j]
                k = j+1
                while k < n:
                    p = k
                    if num[p] == '0':
                        if a+b != 0:
                            break
                        else:
                            res.append(p)
                            a,b = b, a+b
                            k = p+1
                    else:
                        while p < n and int(num[k:p+1]) < a+b:
                            p += 1
                        if int(num[k:p+1]) == a+b and a+b <= 2**31-1:
                            res.append(p)
                            a,b = b, a+b
                            k = p+1
                        else:
                            break
                if k == n:
                    ans = []
                    st = 0
                    for i in res:
                        ans.append(int(num[st:i+1]))
                        st = i+1
                    return ans
        return []
                
        
        