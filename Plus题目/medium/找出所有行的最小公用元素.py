inf  = 0x3f3f3f3f
class Solution:
    def smallestCommonElement(self, mat: List[List[int]]) -> int:
        n, m = len(mat), len(mat[0])
        # O(m * n)
        p = [0] * n
        mx = -inf
        for i in range(n):
            mx = max(mx, mat[i][0])
        while True:
            for i in range(n):
                while p[i] < m and mat[i][p[i]] < mx:
                    p[i] += 1
                if p[i] >= m:
                    return -1 # 不可能到达mx
                else:
                    mx = max(mx, mat[i][p[i]])
            flag = True
            for i in range(n):
                if mat[i][p[i]] != mx:
                    flag = False
                    break
            if flag:
                return mx
        return -1
