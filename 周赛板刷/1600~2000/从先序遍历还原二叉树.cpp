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
    TreeNode* dfs(string s, int depth) {
        vector<pair<int,int>> a;
        int n = s.size(), l = -1;
        for (int i = 0; i < n; ++i) {
            if (isdigit(s[i])) {
                if (l == -1) l = i;
            }
            else {
                if (l != -1) {
                    a.emplace_back(l, i - l);
                    l = -1;
                }
            }
        }
        if (l != -1) a.emplace_back(l, n - l);
        TreeNode* root = new TreeNode(stoi(s.substr(a[0].first, a[0].second)));
        vector<int> son;
        for (int i = 1; i < a.size(); ++i) {
            int tmp = a[i].first - a[i - 1].first - a[i - 1].second;
            if (tmp == depth) son.push_back(i);
        }
        assert(son.size() <= 2);
        if (son.size() == 2) {
            int x1 = a[son[0]].first, x2 = a[son[1]].first;
            root->left = dfs(s.substr(x1, x2 - depth - x1), depth + 1);
            root->right = dfs(s.substr(x2, n - x2), depth + 1);
        }
        else if (son.size() == 1) root->left = dfs(s.substr(a[son[0]].first, n - a[son[0]].first), depth + 1);
        return root;
    }
    TreeNode* recoverFromPreorder(string traversal) {
        return dfs(traversal, 1);
    }
};