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
// 三个指针合并也太麻烦了吧
class Solution {
public:
    vector<int> dfs(TreeNode* root, int k, int& ans) {
        if (!root) return {};
        vector<int> l = dfs(root->left, k, ans);
        vector<int> r = dfs(root->right, k, ans);
        vector<int> cur, test;
        int i = 0, j = 0, flag = 1, tot = 0;
        for (int& v : l) {
            if (v < root->val) ++tot;
            else break;
        }
        for (int& v : r) {
            if (v < root->val) ++tot;
            else break;
        }
        ans += (tot >= k);
        while (cur.size() < k && (i < l.size() || j < r.size() || flag)) {
            if (flag) {
                if (i < l.size() && j < r.size()) {
                    if (root->val < min(l[i], r[j])) cur.push_back(root->val), flag = 0;
                    else {
                        if (i < l.size() && j < r.size()) {
                            if (l[i] < r[j]) cur.push_back(l[i++]);
                            else cur.push_back(r[j++]);
                        }
                        else if (i < l.size()) {
                            cur.push_back(l[i++]);
                        }
                        else cur.push_back(r[j++]);
                    }
                }
                else if (i < l.size()) {
                    if (root->val < l[i]) cur.push_back(root->val), flag = 0;
                    else cur.push_back(l[i++]);
                }
                else if (j < r.size()) {
                    if (root->val < r[j]) cur.push_back(root->val), flag = 0;
                    else cur.push_back(r[j++]);
                }
                else cur.push_back(root->val), flag = 0;
            }
            else {
                if (i < l.size() && j < r.size()) {
                    if (l[i] < r[j]) cur.push_back(l[i++]);
                    else cur.push_back(r[j++]);
                }
                else if (i < l.size()) {
                    cur.push_back(l[i++]);
                }
                else cur.push_back(r[j++]);
            }
        }
        return cur;
    }
    int countGreatEnoughNodes(TreeNode* root, int k) {
        // 暴力区间线段树完全可以做
        // 一次性遍历或者后缀的处理难免都需要将数组排序然后合并（复杂度会很高）
        // 好吧，是我想太多了，实际上 k <= 10， 么实际上就非常简单了就是使用
        // 每一次一边最多上传k个数字即可
        int ans = 0;
        dfs(root, k, ans);
        return ans;
    }
};