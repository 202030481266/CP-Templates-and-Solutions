/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void dfs(vector<vector<int>>& res, vector<int>& cur, vector<int>& a, vector<int>& b, int l, int r) {
        if (l == a.size() && r == b.size()) {
            vector<int> tmp(cur);
            res.push_back(tmp);
            return;
        }
        if (l < a.size()) {
            cur.push_back(a[l]);
            dfs(res, cur, a, b, l + 1, r);
            cur.pop_back();
        }
        if (r < b.size()) {
            cur.push_back(b[r]);
            dfs(res, cur, a, b, l, r + 1);
            cur.pop_back();
        }
    }
    vector<vector<int>> BSTSequences(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return {{}};
        auto left = BSTSequences(root->left);
        auto right = BSTSequences(root->right);
        vector<int> cur{root->val};
        for (auto& u : left)
            for (auto& v : right)
                dfs(ans, cur, u, v, 0, 0); 
        return ans;
    }
};