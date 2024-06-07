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
const int inf = 0x3f3f3f3f;
class Solution {
public:
    tuple<int, int, int> dfs(TreeNode* root, int& ans) {
        if (!root->left&&!root->right) return {root->val,root->val,1};
        bool is_bal = true;
        int sum = 0,mn=root->val,mx=root->val;
        if (root->left) {
            auto [lmin,lmax,lsize] = dfs(root->left,ans);
            if (lmax >= root->val || lsize == 0) is_bal = false;
            sum += lsize;
            mn=min(mn,lmin);
            mx=max(mx,lmax);
        }
        if (root->right) {
            auto [rmin,rmax,rsize] = dfs(root->right,ans);
            if (rmin <= root->val || rsize == 0) is_bal = false;
            sum += rsize;
            mn=min(mn,rmin);
            mx=max(mx,rmax);
        }
        if (is_bal) {
            ans = max(ans, sum+1);
            return {mn,mx,sum+1};
        }
        return {inf,-inf,0};
    }
    int largestBSTSubtree(TreeNode* root) {
        if(!root) return 0;
        int ans = 1;
        dfs(root,ans);
        return ans;
    }
};