# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        def dfs(node, path, target_value):
            if not node:
                return False
            path.append(node)
            if node.val == target_value:
                return True
            if dfs(node.left, path,target_value) or dfs(node.right, path,target_value):
                return True
            path.pop()
            return False
        p1, p2 = [],[]
        if not dfs(root,p1,p.val) or not dfs(root,p2,q.val):
            return None
        i = 0
        while i < len(p1) and i < len(p2) and p1[i] == p2[i]:
            i += 1
        return p1[i-1]
        
            
                
        