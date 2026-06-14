# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def pairSum(self, head: Optional[ListNode]) -> int:
        ans = 0
        arr = []
        cur = head
        while cur:
            arr.append(cur.val)
            cur = cur.next
        n = len(arr)
        l, r = 0, n - 1
        while l < r:
            ans = ans if ans > arr[l] + arr[r] else arr[l] + arr[r]
            l += 1
            r -= 1
        return ans
