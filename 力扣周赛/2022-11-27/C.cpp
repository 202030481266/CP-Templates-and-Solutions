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
    ListNode* removeNodes(ListNode* head) {
        vector<ListNode*> hs;
        vector<int> ans;
        auto temp = head;
        while (temp) {
            hs.emplace_back(temp);
            temp = temp->next;
        }
        int n = hs.size();
        stack<ListNode*> S;
        for (int i = 0; i < n; i++) {
            while (!S.empty() && S.top()->val < hs[i]->val) S.pop();
            S.push(hs[i]);
        }
        while (!S.empty()) {
            ans.emplace_back(S.top()->val);
            S.pop();
        }
        auto hd = new ListNode(ans.back());
        auto res = hd;
        for (int i = ans.size() - 2; i >= 0; i--) {
            auto k = new ListNode(ans[i]);
            hd->next = k;
            hd = k;
        }
        return res;
    }
};