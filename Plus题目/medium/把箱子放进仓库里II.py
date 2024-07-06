inf = 0x3F3F3F3F

class Solution:
    def maxBoxesInWarehouse(self, boxes: List[int], warehouse: List[int]) -> int:
        # 两个方向都可以进入仓库
        # 这个题目还挺有思维的，属于是非经典型的贪心
        # 左右两边有多个相同的可选择位置，无论选择哪个都不会改变最优解(可以简单证明)
        # 在同一阶段,左边x个，右边y个，那么相同条件最多只能装x+y个，一旦这个条件不满足,那么左边x和右边y都将无效，进入下一阶段
        boxes.sort()
        n, m = len(warehouse), len(boxes)
        x = [inf] * n
        y = [inf] * n
        x[0] = warehouse[0]
        y[n - 1] = warehouse[n - 1]
        for i in range(1, n):
            x[i] = min(x[i - 1], warehouse[i])
        for i in range(n - 2, -1, -1):
            y[i] = min(y[i + 1], warehouse[i])
        ini = 0
        for i in range(1, n):
            if (
                min(x[i], y[i]) < min(x[ini], y[ini])
                or min(x[i], y[i]) == min(x[ini], y[ini])
                and max(x[i], y[i]) < max(x[ini], y[ini])
            ):
                ini = i
        print(ini)
        i, j, ans = ini, ini + 1, 0
        p = 0
        while (i >= 0 or j < n) and p < m:
            while i >= 0 and boxes[p] > x[i]:
                i -= 1
            while j < n and boxes[p] > y[j]:
                j += 1
            if i >= 0 and j < n:
                if x[i] < y[j]:
                    i -= 1
                else:
                    j += 1
            elif i >= 0:
                i -= 1
            elif j < n:
                j += 1
            else:
                break
            p += 1
            ans += 1
        return ans
