from typing import List

class Solution:
    def matrixMedian(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        
        # 定义查找的最小值和最大值
        low = min(row[0] for row in grid)
        high = max(row[-1] for row in grid)
        
        desired = (m * n) // 2 + 1
        
        while low < high:
            mid = (low + high) // 2
            place = 0
            
            # 对每一行进行二分查找，统计 <= mid 的元素个数
            for row in grid:
                # 使用二分查找找到第一个大于 mid 的位置
                left, right = 0, n
                while left < right:
                    pivot = (left + right) // 2
                    if row[pivot] <= mid:
                        left = pivot + 1
                    else:
                        right = pivot
                place += left
            
            # 根据统计结果调整搜索范围
            if place < desired:
                low = mid + 1
            else:
                high = mid
        
        return low
