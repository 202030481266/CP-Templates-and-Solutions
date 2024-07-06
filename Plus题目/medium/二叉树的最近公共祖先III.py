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
    def lowestCommonAncestor(self, p: 'Node', q: 'Node') -> 'Node':
        p1 = set()
        cur = p
        while cur:
            p1.add(cur.val)
            cur = cur.parent
        while q.val not in p1:
            q = q.parent
        return q