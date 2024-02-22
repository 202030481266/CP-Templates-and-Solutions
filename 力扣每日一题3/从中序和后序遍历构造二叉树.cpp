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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // 中序： 左子树 根 右子树
        // 后序   左子树 右子树 根
        if (inorder.size() == 0) return nullptr;
        int root = postorder.back(), p = 0;
        for (int i = 0; i < inorder.size(); ++i) {
            if (inorder[i] == root) {
                p = i;
                break;
            }
        }
        vector<int> inorder_left(inorder.begin(), inorder.begin() + p);
        vector<int> inorder_right(inorder.begin() + p + 1, inorder.end());
        vector<int> postorder_left(postorder.begin(), postorder.begin() + p);
        vector<int> postorder_right(postorder.begin() + p, prev(postorder.end()));
        TreeNode* cur = new TreeNode(root);
        cur->left = buildTree(inorder_left, postorder_left);
        cur->right = buildTree(inorder_right, postorder_right);
        return cur;
    }
};