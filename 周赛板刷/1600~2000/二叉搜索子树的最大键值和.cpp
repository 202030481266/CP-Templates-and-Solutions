// https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/



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
    int maxSumBST(TreeNode* root) {
    	unordered_map<TreeNode*, long long> val;
    	unordered_map<TreeNode*, int> mx;
    	unordered_map<TreeNode*, int> mn;

    	function<void(TreeNode*)> dfs = [&](TreeNode* u) {
    		if (u == nullptr) return;
    		dfs(u->left);
    		dfs(u->right);
    		val[u] = mn[u] = mx[u] = u->val;
    		if (u->left) {
    			val[u] += val[u->left]; 
    			mn[u] = min(mn[u], mn[u->left]);
    			mx[u] = max(mx[u], mx[u->left]);
    		}
			if (u->right) {
    			val[u] += val[u->right]; 
    			mn[u] = min(mn[u], mn[u->right]);
    			mx[u] = max(mx[u], mx[u->right]);
    		}
    	};
    	dfs(root);
    	long long ans = INT_MIN;
    	function<bool(TreeNode*)> f = [&](TreeNode* u) {
    		if (u == nullptr) return true;
    		bool left = f(u->left);
    		bool right = f(u->right);
    		if (left && right) {
    			bool l = true, r = true;
    			if (u->left) l = (mx[u->left] < u->val);
    			if (u->right) r = (mn[u->right] > u->val);
    			if (l && r) ans = max(ans, val[u]);
    			return (l && r);
    		}
    		return false;
    	};
    	f(root);
    	return ans;
    }
};