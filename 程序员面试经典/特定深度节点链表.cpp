/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<ListNode*> listOfDepth(TreeNode* tree) {
        vector<ListNode*> ans;
        queue<TreeNode*> q[2];
        int cur = 0;
        ListNode* head = new ListNode(-1);
        ListNode* res = head;

        q[cur].push(tree);
        while (!q[cur].empty()) {
            auto u = q[cur].front();
            q[cur].pop();
            head->next = new ListNode(u->val);
            head = head->next;
            if (u->left) q[cur ^ 1].push(u->left);
            if (u->right) q[cur ^ 1].push(u->right);
            if (q[cur].empty()) {
                if (res->next) 
                    ans.emplace_back(res->next);
                cur ^= 1;
                head = new ListNode(-1);
                res = head;
            }
        }
        return ans;
    }
};