#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<TreeNode*> splitBST(TreeNode* root, int target) {
        auto small = new TreeNode(-1);
        auto big = new TreeNode(-1);
        auto ans1 = small, ans2 = big;

        function<void(TreeNode*)> dfs = [&](TreeNode* root) {
            if (!root) return;
            if (root->val > target) {
                // 添加到big树上
                if (root->val > big->val) {
                    big->right = new TreeNode(root->val, nullptr, root->right);
                    big = big->right;
                }
                else {
                    big->left = new TreeNode(root->val, nullptr, root->right);
                    big = big->left;
                }
                dfs(root->left);
            }
            else {
                if (root->val > small->val) {
                    small->right = new TreeNode(root->val, root->left, nullptr);
                    small = small->right;
                }
                else {
                    small->left = new TreeNode(root->val, root->left, nullptr);
                    small = small->left;
                }
                dfs(root->right);
            }
        };

        dfs(root);
        return {ans1->right, ans2->right};
    }
};
