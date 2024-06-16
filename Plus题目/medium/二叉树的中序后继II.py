"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""

class Solution:
    def inorderSuccessor(self, node: 'Node') -> 'Optional[Node]':
        if node.right:
            # 一定存在右子树中
            node = node.right
            while node.left:
                node = node.left
            return node
        # 可能存在祖先中
        while node.parent and node.parent.val < node.val:
            node = node.parent
        return node.parent

