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
    bool del[1001];
    vector<TreeNode*> roots;
public:
    void dfs(TreeNode* root, bool is_root) {
        if (del[root->val]) {
            if (root->left) dfs(root->left, 1);
            if (root->right) dfs(root->right, 1);
            return;
        }
        if (is_root) roots.emplace_back(root);
        if (root->left) {
            TreeNode* l = root->left;
            if (del[l->val]) {
                root->left = nullptr;
                dfs(l, 1);
            }
            else dfs(l, 0);
        }
        if (root->right) {
            TreeNode* r = root->right;
            if (del[r->val]) {
                root->right = nullptr;
                dfs(r, 1);
            }
            else dfs(r, 0);
        }
    }
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        memset(del, 0, sizeof(del));
        for (int v : to_delete) del[v] = 1;
        dfs(root, 1);
        return roots;
    }
};