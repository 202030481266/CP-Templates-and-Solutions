# 在线算法版本，比较难写，但是仍然是将dfs处理放到了迭代中，算法复杂度和空间复杂度是没有变化的
# 需要使用比较特殊的数据结构来进行在线算法

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class BSTIterator:

    def dfs(self,root):
        if not root:
            return
        self.dfs(root.left)
        self.arr.append(root.val)
        self.dfs(root.right)

    def __init__(self, root: Optional[TreeNode]):
        self.arr = []
        self.dfs(root)
        self.p = -1

    def hasNext(self) -> bool:
        return self.p < len(self.arr)-1

    def next(self) -> int:
        self.p += 1
        return self.arr[self.p] if self.p < len(self.arr) else self.arr[-1]

    def hasPrev(self) -> bool:
        return self.p > 0

    def prev(self) -> int:
        self.p -= 1
        return self.arr[self.p] if self.p >= 0 else self.arr[0]


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.hasNext()
# param_2 = obj.next()
# param_3 = obj.hasPrev()
# param_4 = obj.prev()