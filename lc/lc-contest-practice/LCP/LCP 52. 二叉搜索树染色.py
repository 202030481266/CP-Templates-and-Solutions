# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
from typing import List, Optional
import bisect

class SegmentTree:
    def __init__(self, n):
        self.n = n
        # 开4倍空间来存储线段树节点
        self.tree = [0] * (4 * self.n)
        # 懒标记数组
        self.lazy = [0] * (4 * self.n)
        self.build(0, 0, self.n - 1)
    
    def build(self, node, start, end):
        """构建线段树"""
        if start == end:
            self.tree[node] = 0
            self.lazy[node] = -1
            return
            
        mid = (start + end) // 2
        left_node = 2 * node + 1
        right_node = 2 * node + 2
        
        self.build(left_node, start, mid)
        self.build(right_node, mid + 1, end)
        self.tree[node] = self.tree[left_node] + self.tree[right_node]
    
    def push_down(self, node, start, end):
        """下推懒标记"""
        if self.lazy[node] != -1:
            mid = (start + end) // 2
            left_node = 2 * node + 1
            right_node = 2 * node + 2
            
            # 更新左子树
            self.tree[left_node] = self.lazy[node] * (mid - start + 1)
            self.lazy[left_node] = self.lazy[node]
            
            # 更新右子树
            self.tree[right_node] = self.lazy[node] * (end - mid)
            self.lazy[right_node] = self.lazy[node]
            
            # 清除当前节点的懒标记
            self.lazy[node] = -1
    
    def update_range(self, left, right, val):
        """区间修改接口"""
        self._update_range(0, 0, self.n - 1, left, right, val)
    
    def _update_range(self, node, start, end, left, right, val):
        """区间修改的内部实现"""
        if left > end or right < start:
            return
            
        if left <= start and end <= right:
            # 当前区间被完全包含在要修改的区间内
            self.tree[node] = val * (end - start + 1)
            self.lazy[node] = val
            return
            
        # 下推懒标记
        self.push_down(node, start, end)
        
        mid = (start + end) // 2
        left_node = 2 * node + 1
        right_node = 2 * node + 2
        
        self._update_range(left_node, start, mid, left, right, val)
        self._update_range(right_node, mid + 1, end, left, right, val)
        
        # 更新当前节点的值
        self.tree[node] = self.tree[left_node] + self.tree[right_node]
    
class Solution:
    def getNumber(self, root: Optional[TreeNode], ops: List[List[int]]) -> int:
        arr = []
        
        def dfs(root):
            if not root:
                return
            dfs(root.left)
            arr.append(root.val)
            dfs(root.right)
        dfs(root)

        n = len(arr)
        tree = SegmentTree(n)
        
        for op, L, R in ops:
            L = max(L, arr[0])
            R = min(R, arr[-1])
            if L > R:
                continue
            l = bisect.bisect_left(arr, L)
            r = bisect.bisect_right(arr, R)
            tree.update_range(l, r-1, op)
        
        return tree.tree[0]