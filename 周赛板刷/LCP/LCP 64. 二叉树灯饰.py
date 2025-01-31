# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# 树形DP好题，主要是涉及到了状态转移

class Solution:
    def closeLampInTree(self, root: TreeNode) -> int:
        @cache
        def dfs(u, cur, tot):
            if not u:
                return 0
            cnt = (cur + tot)
            val = u.val if cnt % 2 == 0 else (u.val ^ 1)
            if val:
                res1 = dfs(u.left, 0, tot) + dfs(u.right, 0, tot) + 1
                res2 = dfs(u.left, 1, tot) + dfs(u.right, 1, tot) + 1
                res3 = dfs(u.left, 0, tot ^ 1) + dfs(u.right, 0, tot ^ 1) + 1
                res4 = dfs(u.left, 1, tot ^ 1) + dfs(u.right, 1, tot ^ 1) + 3
            else:
                res1 = dfs(u.left, 0, tot) + dfs(u.right, 0, tot)
                res2 = dfs(u.left, 1, tot) + dfs(u.right, 1, tot) + 2
                res3 = dfs(u.left, 0, tot ^ 1) + dfs(u.right, 0, tot ^ 1) + 2
                res4 = dfs(u.left, 1, tot ^ 1) + dfs(u.right, 1, tot ^ 1) + 2
            return min(res1, res2, res3, res4)
        return dfs(root, 0, 0)

