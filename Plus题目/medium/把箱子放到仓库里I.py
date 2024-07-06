class Solution:
    def maxBoxesInWarehouse(self, boxes: List[int], warehouse: List[int]) -> int:
        # 从左到右进入仓库，那么必然就是从高到低
        boxes.sort(reverse=True)
        p = 0
        pre = 0x3f3f3f3f
        ans = 0
        for i in range(len(warehouse)):
            while p < len(boxes) and boxes[p] > min(pre,warehouse[i]):
                p += 1
            if p < len(boxes):
                ans += 1
                pre = boxes[p]
                p += 1
        return ans