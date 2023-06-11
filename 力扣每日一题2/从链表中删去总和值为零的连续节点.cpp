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
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* dummy = new ListNode(0, head);
        unordered_map<int, vector<ListNode*>> sum;
        sum[0].push_back(dummy);
        ListNode* cur = head;
        int s = 0;
        while (cur) {
            s += cur->val;
            if (sum.count(s)) {
                for (ListNode* c : sum[s])
                    c->next = cur->next;
            }
            sum[s].push_back(cur);
            cur = cur->next;
        }
        return dummy->next;
    }
};