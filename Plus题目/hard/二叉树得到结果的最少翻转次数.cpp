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
    pair<int, int> dfs(TreeNode* root) {
        if (!root->left && !root->right) {
            if (root->val) return {1, 0};
            else return {0, 1};
        }
        if (root->val == 5) {
            auto son = (root->right ? dfs(root->right) : dfs(root->left));
            return {son.second, son.first};
        }
        auto l = dfs(root->left);
        auto r = dfs(root->right);
        if (root->val == 2) { // or
            return {l.first + r.first, min(min(l.first, l.second) + r.second, min(r.first, r.second) + l.second)};
        }
        else if (root->val == 3) { // and
            return {min(min(l.first, l.second) + r.first, min(r.first, r.second) + l.first), l.second + r.second}; 
        }
        else { // xor
            return {min(l.first + r.first, l.second + r.second), min(l.first + r.second, l.second + r.first)};
        }
    }
    int minimumFlips(TreeNode* root, bool result) {
        auto ans = dfs(root);
        return (result ? ans.second : ans.first);
    }
};