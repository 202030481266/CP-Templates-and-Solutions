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
    vector<vector<int>> res;
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        res.resize(2000);
        vector<pair<int, TreeNode*>> q;
        q.emplace_back(1000, root);
        while (!q.empty()) {
            vector<pair<int, TreeNode*>> tmp;
            sort(q.begin(), q.end(), [&](pair<int, TreeNode*>& a, pair<int, TreeNode*>& b){
                return a.first == b.first ? a.second->val < b.second->val : a.first < b.first;
            });
            for (int i = 0; i < q.size(); ++i) {
                res[q[i].first].push_back(q[i].second->val);
                if (q[i].second->left) tmp.emplace_back(q[i].first - 1, q[i].second->left);
                if (q[i].second->right) tmp.emplace_back(q[i].first + 1, q[i].second->right);
            }
            q = tmp;
        }
        vector<vector<int>> ans;
        for (int i = 0; i < 2000; ++i)
            if (res[i].size()) ans.push_back(res[i]);
        return ans;
    }
};