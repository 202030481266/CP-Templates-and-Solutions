from typing import Optional
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def expandBinaryTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if root.left:
            res = self.expandBinaryTree(root.left)
            root.left = TreeNode(val=-1, left=res)
        if root.right:
            res = self.expandBinaryTree(root.right)
            root.right = TreeNode(val=-1, right=res)
        return root