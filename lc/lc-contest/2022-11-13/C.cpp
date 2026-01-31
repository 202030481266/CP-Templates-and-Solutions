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
    int cal(vector<int>& a) {
        if (a.size() == 0) return 0;
        // 离散化
        auto b = a;
        int n = a.size();
        sort(b.begin(), b.end());
        for (int i = 0; i < n; i++) 
            a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        // find different
        int ans = 0;
        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            if (a[i] == i || vis[i]) continue;
            int j = i;
            vis[j] = true;
            while (a[j] != i) {
                ans++;
                j = a[j];
                vis[j] = true;
            }
        }
        // cout << ans << endl;
        return ans;
    }
    int minimumOperations(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int ans = 0;
        while (!q.empty()) {
            auto cur = q;
            vector<int> res;
            while (!cur.empty()) {
                auto u = cur.front();
                cur.pop();
                q.pop();
                if (u->left) {
                    q.push(u->left);
                    res.emplace_back(u->left->val);
                }
                if (u->right) {
                    q.push(u->right);
                    res.emplace_back(u->right->val);
                }
            }
            ans += cal(res);
        }
        return ans;
    }
};