// https://leetcode.cn/problems/maximum-binary-tree/
// 本质就是使用单调栈来构建笛卡尔树
// 因为构建树的过程就是一直往右边插入新的元素，然后寻找到左边第一个比自己大的元素，成为该元素的右儿子，
// 那么弹出的最后一个元素就是新插入元素的左儿子。因此考虑使用单调栈来进行处理。

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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int n = nums.size();
        int top = 0;
        vector<int> s(n + 1);
        vector<TreeNode*> res(n + 1);

        for (int i = 1; i <= n; ++i) 
            res[i] = new TreeNode(nums[i - 1]);
        for (int i = 1; i <= n; ++i) {
            int k = top;
            while (k > 0 && res[s[k]]->val < res[i]->val) --k;
            if (k) res[s[k]]->right = res[i];
            if (k < top) res[i]->left = res[s[k + 1]];
            s[++k] = i;
            top = k;
        }
        TreeNode* ans = res[1];
        for (int i = 2; i <= n; ++i)
            if (res[i]->val > ans->val) ans = res[i];
        return ans;
    }
};