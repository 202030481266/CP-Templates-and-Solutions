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
    void dfs(TreeNode*root, vector<int>& arr) {
        if (!root) return;
        dfs(root->left, arr);
        arr.push_back(root->val);
        dfs(root->right, arr);
    }
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        // 此题简洁的写法应该是很有难度的
        // 进阶的解法复杂度应该是O(logn+k)，因为平衡树的最大高度就是logn
        // 进阶解法其实思路也不是很难，就是使用双栈去模拟就可以了，按照大于和小于分为两个栈
        // 对于广泛意义的二叉树来说肯定是O(n+k)，这道题其实就不难了
        vector<int> arr;
        dfs(root, arr);
        // find latest one that arr[i] <= target
        int l = 0, r = arr.size();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (arr[mid] * 1.0 <= target) l = mid;
            else r = mid;
        }
        vector<int> ans;
        r = l + 1;
        while (k--) {
            if (l >= 0 && r < arr.size()) {
                if (abs(1.0 * arr[l] - target) < abs(1.0 * arr[r] - target)) 
                    ans.push_back(arr[l--]);
                else ans.push_back(arr[r++]);
            }
            else if (l >= 0) ans.push_back(arr[l--]);
            else ans.push_back(arr[r++]);
        }
        return ans;
    }
};