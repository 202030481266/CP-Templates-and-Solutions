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
    vector<int> nextLargerNodes(ListNode* head) {
        auto t = head;
        vector<int> a;
        while (t) a.emplace_back(t->val), t = t->next;

        int n = a.size();
        vector<int> ans(n);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && a[s.top()] < a[i]) {
                ans[s.top()] = a[i];
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};