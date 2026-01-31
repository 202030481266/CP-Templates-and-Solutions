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
    TreeNode* replaceValueInTree(TreeNode* root) {
        vector<TreeNode*> q;  // 当前节点，父节点
        q.emplace_back(root);
        root->val = 0;
        while (!q.empty()) {
            vector<TreeNode*> tmp;
            vector<int> sum(q.size() + 1, 0);
            // 添加新的节点入队列
            for (int i = 0; i < q.size(); ++i) {
                if (q[i]->left) tmp.emplace_back(q[i]->left), sum[i + 1] += q[i]->left->val;
                if (q[i]->right) tmp.emplace_back(q[i]->right), sum[i + 1] += q[i]->right->val;
                sum[i + 1] += sum[i];
            }
            if (tmp.size() == 0) break;
            if (sum.size() > 2) {
                // 大于2组
                for (int i = 0; i < q.size(); ++i) {
                    if (q[i]->left) q[i]->left->val = sum[i] + sum.back() - sum[i + 1];
                    if (q[i]->right) q[i]->right->val = sum[i] + sum.back() - sum[i + 1];
                }
            } else {
                if (q[0]->left) q[0]->left->val = 0;
                if (q[0]->right) q[0]->right->val = 0;
            }
            q = move(tmp);
        }
        return root;
    }
};