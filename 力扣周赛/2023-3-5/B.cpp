/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        if (!root) return {};
        vector<long long> ans;
        queue<TreeNode*> q, cur;

        q.push(root);
        while (!q.empty()) {
            cur = q;
            long long res = 0;
            while (!cur.empty()) {
                auto t = cur.front();
                q.pop();
                cur.pop();
                res += t->val;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            ans.emplace_back(res);
        }
        if (ans.size() < k) return -1;
        sort(ans.begin(), ans.end());
        return ans[ans.size() - k];
    }
};