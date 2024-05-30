#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

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
    void dfs(TreeNode* root, unordered_map<TreeNode*,int>& h, unordered_map<TreeNode*, TreeNode*>& fa) {
        h[root] = 0;
        if (root->left) {
            h[root] += 1;
            fa[root->left] = root;
            dfs(root->left, h, fa);
        }
        if (root->right) {
            h[root] += 1;
            fa[root->right] = root;
            dfs(root->right, h, fa);
        }
    }
    vector<vector<int>> findLeaves(TreeNode* root) {
        // 拓扑排序
        unordered_map<TreeNode*, int> cnt;
        unordered_map<TreeNode*, TreeNode*> fa;
        dfs(root, cnt, fa);
        vector<TreeNode*> q;
        vector<vector<int>> ans;
        for (auto [k,v]: cnt) {
            if (v==0) q.push_back(k);
        }
        while (!q.empty()) {
            vector<TreeNode*> tmp;
            vector<int> res;
            for (auto u : q) {
                res.push_back(u->val);
                cnt[fa[u]] -= 1;
                if (cnt[fa[u]] == 0) {
                    tmp.push_back(fa[u]);
                }
            }
            q = move(tmp);
            ans.push_back(res);
        }
        return ans;
    }
};