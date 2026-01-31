// 观察到一个重要的事实： 最后的能够生成的合法的BST一定是固定的。
// 后面就是模拟就可以了


class Solution {
    int n, vis[50010];
    TreeNode* idx[50010];
    unordered_map<int, TreeNode*> son[50010];
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, nullptr, nullptr);
    }
    bool isValidBST(TreeNode* root, TreeNode* min, TreeNode* max) {
        if (!root) return true;

        if (min && root->val <= min->val) return false;
        if (max && root->val >= max->val) return false;

        return isValidBST(root->left, min, root)
            && isValidBST(root->right, root, max);
    }
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        n = trees.size();
        for (auto& c : trees) {
            if (!c->left && !c->right) {
                son[c->val][c->val] = c;
            }
            else {
                if (c->left) son[c->val][c->left->val] = c->left;
                if (c->right) son[c->val][c->right->val] = c->right;
            }
            vis[c->val] = 1;
            idx[c->val] = c;
        }
        queue<pair<int, TreeNode*>> q;
        for (int i = 0; i < n; ++i) {
            if (!vis[trees[i]->val]) continue; // is merged
            for (auto& c : son[trees[i]->val]) q.emplace(c);
            while (!q.empty()) {
                auto [u, w] = q.front();
                q.pop();
                if (vis[u] && idx[u] != trees[i]) {  // root, can not merge itself
                    vis[u] = 0;
                    w->left = idx[u]->left;
                    w->right = idx[u]->right;
                    for (auto& v : son[u]) 
                        q.emplace(v);
                }
            }
        }
        int cnt = 0;
        TreeNode* ans = nullptr;
        for (auto& c : trees)
            if (vis[c->val]) ++cnt, ans = c;
        if (cnt > 1) return nullptr;
        return isValidBST(ans) ? ans : nullptr;
    }
};