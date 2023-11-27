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
    int ans = 0;
public:
    void dfs(TreeNode* root, int status) {
        status ^= (1 << root->val);
        if (!root->left && !root->right) {
            // 叶子
            if (__builtin_popcount(status) <= 1) ans += 1;
            return;
        }
        if (root->left) dfs(root->left, status);
        if (root->right) dfs(root->right, status);
    }
    int pseudoPalindromicPaths (TreeNode* root) {
        if (!root) return 0;
        dfs(root, 0);
        return ans;
    }
};