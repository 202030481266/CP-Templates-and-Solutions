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
    int ans;
public:
    int dfs(TreeNode* root) {
        if (!root) return NULL;
        int l = dfs(root->left), r = dfs(root->right);
        if (root->left && root->right) {
            if (l == 0 && r == 0) {
                ++ans;
                return 1;
            }
            return (l == 0 || r == 0 ? 1 : 2);
        }
        else return (!root->left ? r : l);
    }
    int navigation(TreeNode* root) {
        if (!root) return 0;
        int l = dfs(root->left), r = dfs(root->right);
        if (l + r >= 2) return ans;
        return ans + 1;
    }
};