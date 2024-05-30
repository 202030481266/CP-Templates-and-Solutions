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
    void dfs1(TreeNode* root, int& l, int& r, int c) {
        if (!root) return;
        l = min(l, c);
        r = max(r, c);
        dfs1(root->left,l,r,c-1);
        dfs1(root->right,l,r,c+1);
    }
    vector<vector<int>> verticalOrder(TreeNode* root) {
        // 这道题的排序比较复杂
        if (!root) return {};
        int tot = 0, l = 0, r = 0;
        dfs1(root,l,r,0);
        vector<TreeNode*> column[r-l+1];
        unordered_map<TreeNode*, int> dep,dfn;
        function<void(TreeNode*,int,int)> dfs = [&](TreeNode* root, int d, int c) {
            if(!root) return;
            dfn[root] = ++tot;
            dep[root] = d;
            column[c].push_back(root);
            dfs(root->left, d+1, c-1);
            dfs(root->right, d+1, c+1);
        };
        dfs(root,0,-l); // l->0,0->-l
        vector<vector<int>> ans;
        for (auto& col : column) {
            sort(col.begin(), col.end(), [&](TreeNode* a, TreeNode* b) {
                return dep[a] == dep[b] ? dfn[a] < dfn[b] : dep[a] < dep[b];
            });
            vector<int> tmp;
            for (auto& node : col) {
                tmp.push_back(node->val);
            }
            ans.push_back(tmp);
        }
        return ans;
    }
};