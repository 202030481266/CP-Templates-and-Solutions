# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

from typing import Optional
from collections import defaultdict

class Solution:
    def deleteDuplicatesUnsorted(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(val=-1,next=head)
        cur = head

        cnt = defaultdict(int)
        while cur:
            cnt[cur.val] += 1
            cur = cur.next

        s = {k for k, v in cnt.items() if v > 1}
        cur = dummy
        while cur and cur.next:
            p = cur.next
            while p and p.val in s:
                p = p.next
            cur.next = p
            cur = cur.next
        return dummy.next

        