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
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        function<int(TreeNode* &, int)> dfs = [&](TreeNode* &root, int sum) -> int {
            if (!root) return INT_MIN;
            int left = dfs(root->left, sum + root->val);
            int right = dfs(root->right, sum + root->val);
            int tmp = max(left, right), res = root->val;
            tmp = (tmp == INT_MIN ? 0 : tmp);
            if (tmp + res + sum < limit) root = nullptr;
            return tmp + res;
        };
        dfs(root, 0);
        return root;
    }
};