# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def findNearestRightNode(self, root: TreeNode, u: TreeNode) -> Optional[TreeNode]:
        q = [root]
        while q:
            tmp = []
            for i in range(len(q)):
                if q[i] == u:
                    return q[i+1] if i+1 < len(q) else None
                if q[i].left:
                    tmp.append(q[i].left)
                if q[i].right: 
                    tmp.append(q[i].right)
            q = tmp
        return None