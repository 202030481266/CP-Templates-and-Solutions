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
    int closestValue(TreeNode* root, double target) {
        // 要么是前驱要么是后继
        if (root->val * 1.0 == target) return root->val;
        else if (root->val * 1.0 > target) {
            if (root->left) {
                int res = closestValue(root->left, target);
                double x = abs(target - res * 1.0), y = 1.0 * root->val - target;
                if (x <= y) return res;
                else return root->val;
            }
            else return root->val;
        }
        else {
            if (root->right) {
                int res = closestValue(root->right, target);
                double x = abs(target - res * 1.0), y = target - 1.0 * root->val;
                if (x < y) return res;
                else return root->val;
            }
            else return root->val;
        }
    }
};