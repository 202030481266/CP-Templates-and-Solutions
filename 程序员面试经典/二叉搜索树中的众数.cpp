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
	int pre, cnt, mx;
public:
    vector<int> findMode(TreeNode* root) {
    	pre = 0x3f3f3f3f, cnt = 0, mx = 0;
    	// dfs
    	vector<int> ans;
    	function<void(TreeNode*)> get_mx = [&](TreeNode* u) {
    		if (!u) return;
    		get_mx(u->left);
    		if (u->val != pre) {
    			pre = u->val;
    			cnt = 1;
    		} else ++cnt;
    		mx = max(mx, cnt);
    		get_mx(u->right);
    	};
    	get_mx(root);
    	pre = 0x3f3f3f3f, cnt = 0;
    	function<void(TreeNode*)> dfs = [&](TreeNode* u) {
    		if (!u) return;
    		dfs(u->left);
    		if (u->val != pre) {
    			pre = u->val;
    			cnt = 1;
    		}
    		else ++cnt;
    		if (cnt == mx) ans.emplace_back(u->val);
    		dfs(u->right);
    	};
    	dfs(root);
    	return ans;
    }
};