from typing import List

class Solution:
    def change(self, a) -> list:
        n = len(a)
        b = [0] * n
        j = 0
        for i in range(1, n, 2):
            b[j] = a[i]
            j += 1
        for i in range(0, n, 2):
            b[j] = a[i]
            j += 1
        return b

    def isMagic(self, target: List[int]) -> bool:
        s = target
        n = len(target)
        a = list(range(1, n+1))
        k = 0
        while s:
            tmp = a[0]
            while s[0] != a[0]:
                a = self.change(a)
                if a[0] == tmp:
                    return False
            i = 0
            while i < len(s) and s[i] == a[i]:
                i += 1
            if k == 0:
                k = i
            else:
                if k != i and i != len(s): # [0, i)
                    return False
            if i == len(s):
                break
            s = s[i:]
            a = a[i:]
        return True
        
            
