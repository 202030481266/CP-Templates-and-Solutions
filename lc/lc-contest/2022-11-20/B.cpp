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
    void dfs(TreeNode* root, vector<int>& a) {
        if (root == nullptr) return;
        dfs(root->left, a);
        a.emplace_back(root->val);
        dfs(root->right, a);
    }
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        vector<vector<int>> ans(queries.size(), vector<int>(2));
        vector<int> val;

        dfs(root, val);
        for (int i = 0; i < queries.size(); i++) {
            auto t = lower_bound(val.begin(), val.end(), queries[i]) - val.begin();
            if (t != val.size() && val[t] == queries[i]) {
                ans[i][0] = ans[i][1] = val[t];
                continue;
            }
            // right
            if (t != val.size()) ans[i][1] = val[t];
            else ans[i][1] = -1;
            // left
            if (t >= 1) ans[i][0] = val[t - 1];
            else ans[i][0] = -1;
        }

        return ans;
    }
};