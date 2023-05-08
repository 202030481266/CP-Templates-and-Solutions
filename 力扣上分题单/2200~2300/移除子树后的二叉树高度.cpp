// https://leetcode.cn/problems/height-of-binary-tree-after-subtree-removal-queries/
// 此问题不可能存在log级别的查询方法，所以果断肯定有预处理全部答案的方法
// 可以使用两次DFS或者DFS序转换为区间问题


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
	unordered_map<TreeNode*, int> h;
	unordered_map<int, int> res;
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
    	function<int(TreeNode*)> f = [&](TreeNode* u) -> int {
    		return h[u] = (u ? 1 + max(f(u->left), f(u->right)) : 0);
    	};
    	f(root);
    	// 下面的dfs非常巧妙
    	function<void(TreeNode*, int, int)> dfs = [&](TreeNode* u, int depth, int ans) {
    		if (!u) return;
    		res[u->val] = ans;
    		dfs(u->left, depth + 1, max(depth + 1 + h[u->right], ans));
    		dfs(u->right, depth + 1, max(depth + 1 + h[u->left], ans));
    	};
    	dfs(root, -1, 0);
    	vector<int> ans(queries.size());
    	for (int i = 0; i < ans.size(); ++i) ans[i] = res[queries[i]];
    	return ans;
    }
};
