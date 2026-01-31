# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from collections import defaultdict
class Solution:
    def heightOfTree(self, root: Optional[TreeNode]) -> int:
        # dep_son = dep_fa + 1 is a direct
        # very tricky problem
        dep = defaultdict(int)
        def dfs(u):
            nonlocal dep
            if u.left and (not u.left.left or u.left.left.val != u.val) and (not u.left.right or u.left.right.val != u.val):
                dep[u.left] = dep[u] + 1
                dfs(u.left)
            if u.right and (not u.right.left or u.right.left.val != u.val) and (not u.right.right or u.right.right.val != u.val):
                dep[u.right] = dep[u] + 1
                dfs(u.right)
        dfs(root)
        return max(dep.values())

        