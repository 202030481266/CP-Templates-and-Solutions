# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
from collections import defaultdict

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', nodes: 'List[TreeNode]') -> 'TreeNode':
        sz = defaultdict(int)
        dfn = defaultdict(int)
        tot = 0
        def dfs(u):
            nonlocal tot
            if not u:
                return 0
            tot += 1
            dfn[u.val] = tot
            sz[u.val] = 1
            sz[u.val] += dfs(u.left)
            sz[u.val] += dfs(u.right)
            return sz[u.val]
        dfs(root)
        mn = dfn[nodes[0].val]
        mx = dfn[nodes[0].val]
        for i in range(1,len(nodes)):
            mn = min(mn, dfn[nodes[i].val])
            mx = max(mx, dfn[nodes[i].val])
        ans = None
        def find(u):
            nonlocal ans, dfn, sz, mn, mx
            if not u: 
                return
            if dfn[u.val] <= mn and dfn[u.val] + sz[u.val] - 1 >= mx:
                ans = u
                find(u.left)
                find(u.right)
        find(root)
        return ans


            