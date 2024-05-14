# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def getDirections(self, root: Optional[TreeNode], startValue: int, destValue: int) -> str:
        fa = {}
        dep = {}
        d = {}
        x, y = None, None
        def dfs(root, startValue, destValue):
            nonlocal x, y
            if root.val == startValue:
                x = root
            if root.val == destValue:
                y = root
            if root.left:
                fa[root.left] = root
                d[root.left] = "L"
                dep[root.left] = dep[root] + 1
                dfs(root.left, startValue, destValue)
            if root.right:
                fa[root.right] = root
                d[root.right] = "R"
                dep[root.right] = dep[root] + 1
                dfs(root.right, startValue, destValue)
        fa[root] = root
        dep[root] = 0
        dfs(root, startValue, destValue)
        p1 , p2 = "" ,""
        # print(x, y)
        while dep[x] > dep[y]:
            x = fa[x]
            p1 += "U"
        while dep[y] > dep[x]:
            p2 += d[y]
            y = fa[y]
        while x != y:
            p2 += d[y]
            p1 += "U"
            x = fa[x]
            y = fa[y]
        return p1 + p2[::-1]


        

        
        
         
        
            
            