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
const int mod = 1e9 + 7;
class Solution {
    using ll = long long;
public:
    ll dfs(TreeNode* root) {
        if (!root) return 0;
        return (dfs(root->left) + root->val + dfs(root->right));
    }
    ll f(TreeNode* root, ll& ans, ll& sum) {
        if (!root) return 0;
        ll sl = f(root->left, ans, sum);
        ll sr = f(root->right, ans, sum);
        ans = max(ans, sl * (sum - sl));
        ans = max(ans, sr * (sum - sr));
        return sl + sr + root->val;
    }
    int maxProduct(TreeNode* root) {
        ll sum = dfs(root);
        ll ans = 0;
        f(root, ans, sum);
        return ans % mod;
    }
};