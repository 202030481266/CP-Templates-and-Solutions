# 有趣的数学题目

class Solution:
    def orchestraLayout(self, n: int, x: int, y: int) -> int:
        # 4 * (n-1)
        # num, num-2, num-4, ... num-mn*2+2, num-mn*2
        # num-1, num-3, num-5, ..., num-mn*2+1, num-mn*2-1
        # 0, 1, 2, 3, 4, ..., mn-1, mn
        mid = n//2
        if n&1:
            mn = mid-max(abs(x-mid), abs(y-mid))
        else:
            mid = n//2
            mx1 = abs(x-mid) if x >= mid else abs(x-mid+1)
            mx2 = abs(y-mid) if y >= mid else abs(y-mid+1)
            mn = mid-1-max(mx1, mx2)
        tot = (n-mn*2+1+n-1)*mn*2
        start = tot%9
        # (mn,mn), (mn, num-mn-1), (num-mn-1, num-mn-1), (num-mn-1, mn)
        walk = 0
        if x == mn:
            walk = y-mn
        elif x == n-mn-1:
            walk = 2*(n-mn*2-1)+(n-mn-1-y)
        else:
            if y == n-mn-1:
                walk = n-mn*2-1+(x-mn)
            else:
                walk = 3*(n-mn*2-1)+(n-mn-1-x)     
        return (start+walk)%9+1