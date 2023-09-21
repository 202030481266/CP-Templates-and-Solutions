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
    unordered_map<TreeNode*, int> f, g;
public:
    void dfs(TreeNode* root) {
        f[root] += root->val;
        if (root->left) {
            dfs(root->left);
            g[root] += max(g[root->left], f[root->left]);
            f[root] += g[root->left];
        }
        if (root->right) {
            dfs(root->right);
            g[root] += max(g[root->right], f[root->right]);
            f[root] += g[root->right];
        }
    }
    int rob(TreeNode* root) {
        dfs(root);
        return max(f[root], g[root]);
    }
};