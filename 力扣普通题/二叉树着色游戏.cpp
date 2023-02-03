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
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        // 左右子树大小问题
        vector<int> siz(n + 1, 0);
        TreeNode* p_x = nullptr;

        function<int(TreeNode*)> cal_siz = [&](TreeNode* root) {
            if (root == nullptr) return 0;
            if (root->val == x) p_x = root;  // get the treeNode
            siz[root->val] = 1;
            siz[root->val] += cal_siz(root->left);
            siz[root->val] += cal_siz(root->right);
            return siz[root->val];
        };
        cal_siz(root);
        if (x != root->val) {
            // x is not root
            // 往上封锁
            if (n - siz[x] > siz[x]) return true;
        }
        // 往下取
        if (p_x->left && p_x->right) {
            int t = max(siz[p_x->left->val], siz[p_x->right->val]);
            if (t > n - t) return true;
        } else if (p_x->left) {
            if (siz[p_x->left->val] > n - siz[p_x->left->val]) return true;
        } else if (p_x->right) {
            if (siz[p_x->right->val] > n - siz[p_x->right->val]) return true;
        }
        return false;
    }
};