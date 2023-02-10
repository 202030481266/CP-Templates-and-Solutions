/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 双dfs

class Solution {
public:
    bool dfs(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) return true;
        if (!t1 || !t2) return false;
        return (t1->val == t2->val) && dfs(t1->left, t2->left) && dfs(t1->right, t2->right);
    }
    bool checkSubTree(TreeNode* t1, TreeNode* t2) {
        if (!t1) return !t2;
        return dfs(t1, t2) || checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
    }
};