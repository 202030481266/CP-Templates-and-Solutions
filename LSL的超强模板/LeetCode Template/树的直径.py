# https://leetcode.cn/problems/diameter-of-n-ary-tree/

"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []
"""

class Solution:
    def diameter(self, root: 'Node') -> int:
        """
        :type root: 'Node'
        :rtype: int
        """
        self.max_diameter = 0
        
        def dfs(node):
            if not node:
                return 0
            
            # 找到当前节点子节点中最长的两条路径
            max_depths = [0, 0]
            for child in node.children:
                depth = dfs(child)
                if depth > max_depths[0]:
                    max_depths[0], max_depths[1] = depth, max_depths[0]
                elif depth > max_depths[1]:
                    max_depths[1] = depth
            
            # 计算通过当前节点的最大直径（最长子路径+次长子路径）
            current_diameter = max_depths[0] + max_depths[1]
            self.max_diameter = max(self.max_diameter, current_diameter)
            
            # 返回从当前节点出发的最大深度
            return max_depths[0] + 1
        
        dfs(root)
        return self.max_diameter
        
            