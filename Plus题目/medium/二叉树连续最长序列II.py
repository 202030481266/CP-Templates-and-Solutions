# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def longestConsecutive(self, root: Optional[TreeNode]) -> int:
        ans = 1
        def dfs(u):
            nonlocal ans
            inc,dec = 1,1
            if not u.left and not u.right:
                return (inc,dec)
            elif u.left and u.right:
                l_inc,l_dec = dfs(u.left)
                r_inc,r_dec = dfs(u.right)
                # 考虑左右连接
                if u.left.val == u.val + 1 and u.right.val == u.val - 1:
                    ans = max(ans, l_inc + r_dec + 1)
                if u.left.val == u.val - 1 and u.right.val == u.val + 1:
                    ans = max(ans, l_dec + r_inc + 1)
                if u.left.val == u.val + 1:
                    inc = max(inc, l_inc + 1)
                if u.left.val == u.val - 1:
                    dec = max(dec, l_dec + 1)
                if u.right.val == u.val + 1:
                    inc = max(inc, r_inc + 1)
                if u.right.val == u.val - 1:
                    dec = max(dec, r_dec + 1)
            elif u.left:
                l_inc, l_dec = dfs(u.left)
                if u.left.val == u.val + 1:
                    inc = l_inc + 1
                if u.left.val == u.val - 1:
                    dec = l_dec + 1
            else:
                r_inc,r_dec = dfs(u.right)
                if u.right.val == u.val + 1:
                    inc = r_inc + 1
                if u.right.val == u.val - 1:
                    dec = r_dec + 1
            ans = max(ans, inc, dec)
            return (inc,dec)
        dfs(root)
        return ans
