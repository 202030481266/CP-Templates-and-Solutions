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
    int ans;
public:
    pair<int, int> dfs(TreeNode* root) {
        if (!root) return {-1, -1};
        auto [l_mn, l_mx] = dfs(root->left);
        auto [r_mn, r_mx] = dfs(root->right);
        int mn = INT_MAX, mx = INT_MIN;
        if (l_mn != -1) mn = min(mn, l_mn);
        if (r_mn != -1) mn = min(mn, r_mn);
        if (l_mx != -1) mx = max(mx, l_mx);
        if (r_mx != -1) mx = max(mx, r_mx);
        if (mn != INT_MAX) ans = max(ans, abs(root->val - mn));
        if (mx != INT_MIN) ans = max(ans, abs(root->val - mx));
        return {min(mn, root->val), max(mx, root->val)};
    }
    int maxAncestorDiff(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};