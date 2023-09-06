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
// 树上多个点的LCA，就是DFS序最小的和DFS序最大的这两个点的LCA
class Solution {
    int fa[1010], d[1010], ans = -1, mn = 1008, mx = 1009, dfn[1010], tot = 0;
    unordered_map<int, TreeNode*> h;
public:
    void dfs(TreeNode* u, int f, int dep) {
        if (!u) return;
        fa[u->val] = f;
        d[u->val] = dep;
        dfn[u->val] = ++tot;
        h[u->val] = u;
        dfs(u->left, u->val, dep + 1);
        dfs(u->right, u->val, dep + 1);
        if (!u->left && !u->right) ans = max(ans, d[u->val]);
    }
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        memset(fa, -1, sizeof(fa));
        dfs(root, -1, 1);
        dfn[mn] = 1010;
        dfn[mx] = 0;
        // cout << ans << endl;
        for (int i = 0; i < 1010; ++i)
            if (d[i] == ans) {
                // cout << i << ' ' << dfn[i] << '\n';
                if (dfn[i] < dfn[mn]) mn = i;
                if (dfn[i] > dfn[mx]) mx = i;
            }
        // cout << mn << ' ' << mx << '\n';
        while (mn != mx && mn != -1 && mx != -1) {
            mn = fa[mn];
            mx = fa[mx];
        }
        return h[mn];
    }
};