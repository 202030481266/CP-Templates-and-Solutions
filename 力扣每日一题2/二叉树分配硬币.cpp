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
    unordered_map<TreeNode*, int> siz;
    unordered_map<TreeNode*, int> f;
    int ans = 0;
public:
    void dfs0(TreeNode* root) {
        if (!root) return;
        siz[root] = 1;
        f[root] = root->val;
        dfs0(root->left);
        dfs0(root->right);
        siz[root] += siz[root->left];
        siz[root] += siz[root->right];
        f[root] += f[root->left];
        f[root] += f[root->right];
    }
    void dfs1(TreeNode* root) {
        if (!root) return;
        dfs1(root->left);
        dfs1(root->right);
        ans += abs(f[root->left] - siz[root->left]);
        ans += abs(f[root->right] - siz[root->right]);
    }
    int distributeCoins(TreeNode* root) {
        dfs0(root);
        dfs1(root);
        return ans;
    }
};