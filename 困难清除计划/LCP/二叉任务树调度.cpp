// xiaoshulin
// 2023.12.14

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
	using pii = pair<int, int>;
public:
	pii dfs(TreeNode* root) {
		if (!root) return {0, 0};
		int siz = root->val, mn = 0;
		pii left = dfs(root->left);
		pii right = dfs(root->right);
		siz += left.first + right.first;
		if (left.first == right.first) {
			return {siz, left.first * 2};
		}
		else if (left.first > right.first) {
			int tmp = left.first - right.first;
			if (left.second >= tmp) return {siz, left.first + right.first};
			else return {siz, right.first * 2 + left.second};
		}
		else {
			int tmp = right.first - left.first;
			if (right.second >= tmp) return {siz, right.first + left.first};
			else return {siz, left.first * 2 + right.second};
		}
		return {0, 0};
	}
    double minimalExecTime(TreeNode* root) {
		pii res = dfs(root);
		return 1.0 * res.first - res.second + res.second / 2.0;
    }
};
