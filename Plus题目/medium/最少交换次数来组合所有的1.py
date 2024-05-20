class Solution:
    # 相邻位置交换的版本
    def minSwaps(self, data: List[int]) -> int:
        pos = []
        n = len(data)
        for i in range(n):
            if data[i] > 0:
                pos.append(i)
        # i + m - 1 < n , i < n - m + 1
        m = len(pos)
        p, cur, s = 0, 0, sum(pos)
        ans = 0x3f3f3f3f
        for i in range(n-m+1):
            # 枚举窗口
            while p < m and pos[p] < i + p:
                cur += pos[p]
                p += 1
            # [0, p-1] 是左边的窗口外的1的位置，对应了 i,i+1,i+2,...,i+p-1
            # [p, m-1] 是右边的窗口位置，对应了,i+p,i+p+1,...,i+m-1
            left = (i+p-1+i) * p // 2 - cur
            right = (s-cur) - (i+p+i+m-1) * (m-p) // 2
            ans = min(ans, left+right)
        return ans

