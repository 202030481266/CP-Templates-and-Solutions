# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
def prettyPrintLinkedList(node):
    while node and node.next:
        print(str(node.val) + "->", end='')
        node = node.next

    if node:
        print(node.val)
    else:
        print("Empty LinkedList")
class Solution:
    def plusOne(self, head: ListNode) -> ListNode:
        # 反转链表
        pre, cur = None, head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        head = pre
        add = 1
        cur = head
        while add and cur:
            t = cur.val + add
            cur.val = t % 10
            add = t // 10
            if add and not cur.next:
                cur.next = ListNode(0,None)
            cur = cur.next
        # 再次反转链表
        pre, cur = None, head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre