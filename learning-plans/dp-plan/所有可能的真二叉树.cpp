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
    TreeNode* get() {
        TreeNode* node = new TreeNode(0);
        return node;
    }
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        if (n % 2 == 0) return {};
        if (n == 1) return {get()};
        vector<TreeNode*> res;
        for (int i = 1; i < n - 1; i += 2) {
            vector<TreeNode*> left = allPossibleFBT(i);
            vector<TreeNode*> right = allPossibleFBT(n - 1 - i);
            for (TreeNode* u : left)
                for (TreeNode* v : right) {
                    TreeNode* cur = get();
                    cur->left = u;
                    cur->right = v;
                    res.push_back(cur);
                }
        }
        return res;
    }
};