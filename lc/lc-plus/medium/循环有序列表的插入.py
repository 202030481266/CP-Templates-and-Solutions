# 看起来简单，实际上非常不好做的一道思维题目

"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':
        if not head:
            t = Node(insertVal)
            t.next = t
            return t
        # 所以值相同的情况会出现迷惑现象
        inf = 0x3f3f3f3f
        stop_node = Node(inf) # 哨兵
        stop_node.next = head.next
        head.next = stop_node
        p = stop_node.next
        while p.next.val != inf and p.next.val >= p.val:
            p = p.next
        head.next = stop_node.next
        if insertVal >= p.val or insertVal <= p.next.val:
            t = Node(insertVal,p.next)
            p.next = t
        else:
            p = p.next
            while p.val <= insertVal and p.next.val <= insertVal:
                p = p.next
            t = Node(insertVal,p.next)
            p.next = t
        return head
            
        