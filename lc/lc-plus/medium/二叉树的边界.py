# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
# 挺不好做的一道题目
class Solution:
    def boundaryOfBinaryTree(self, root: Optional[TreeNode]) -> List[int]:
        # 四种情况
        ans = []
        def dfs(node, flag):
            nonlocal ans
            if not node.left and not node.right:
                ans.append(node.val)
                return
            if flag == 0:
                if node.left:
                    dfs(node.left, 0)
                if node.right:
                    dfs(node.right, 0)
            elif flag == 1: # 左边界
                ans.append(node.val)
                if node.left:
                    dfs(node.left, 1)
                    if node.right:
                        dfs(node.right, 0)
                else:
                    dfs(node.right, 1)
            elif flag == 2: # 右边界
                if node.right:
                    if node.left:
                        dfs(node.left,0)
                    dfs(node.right,2)
                else:
                    dfs(node.left,2)
                ans.append(node.val)
            else: # 双边界
                ans.append(node.val)
                if node.left and node.right:
                    dfs(node.left,1)
                    dfs(node.right,2)
                elif node.left:
                    dfs(node.left,1)
                else:
                    dfs(node.right,2)
        dfs(root, 3)
        return ans
        
                    
