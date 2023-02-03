/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode *l = list1;

        for (int i = 0; i < a - 1; ++i) if (l) l = l->next;
        ListNode *r = l;
        for (int i = 0; i < (b - a + 2); ++i) if (r) r = r->next;

        ListNode* tail = list2;
        while (tail && tail->next) tail = tail->next;
        if (l) l->next = list2;
        tail->next = r;
        return list1;
    }
};