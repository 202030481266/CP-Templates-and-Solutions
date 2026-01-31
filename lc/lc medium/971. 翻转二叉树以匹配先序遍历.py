# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from typing import Optional, List

class Solution:
    def flipMatchVoyage(self, root: Optional[TreeNode], voyage: List[int]) -> List[int]:
        self.idx = 0
        self.ans = []
        def dfs(node):
            if not node or self.ans and self.ans[0] == -1:
                return
            if node.val != voyage[self.idx]:
                self.ans = [-1]
                return
            self.idx += 1
            if self.idx < len(voyage) and node.left and node.left.val != voyage[self.idx]:
                self.ans.append(node.val)
                dfs(node.right)
                dfs(node.left)
            else:
                dfs(node.left)
                dfs(node.right)
        dfs(root)
        return self.ans