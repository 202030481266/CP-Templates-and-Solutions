// https://leetcode.cn/problems/tree-of-coprimes/



class Solution {
	int cnt[60];
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
    	// 寻找每一个节点的最近互质祖先
    	// 关键点1：1 <= nums[i] <= 50
    	int n = nums.size();
    	vector<int> ans(n), f(n);
    	vector<int> g[n];
    	vector<int> a[60];
    	memset(cnt, 0, sizeof(cnt));
    	// 建图
    	for (auto &c : edges) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    	}
    	// 寻找可能的GCD
    	for (int i = 1; i <= 50; ++i) 
    		for (int j = i; j <= 50; ++j) // 注意 gcd(1,1)==1
    			if (gcd(i, j) == 1) {
    				a[i].emplace_back(j);
    				a[j].emplace_back(i);
    			}
    	// dfs
    	vector<pair<int, int>> cur[60]; // [depth, index]
    	function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
    		// 统计结果
				f[u] = fa;
    		int mx = -1, idx = -1;
    		for (int c : a[nums[u]]) {
    			if (cnt[c]) {
    				if (cur[c].back().first > mx) 
    					mx = cur[c].back().first, idx = cur[c].back().second;
    			}
    		}
    		ans[u] = idx;
    		// 添加
    		++cnt[nums[u]];
    		cur[nums[u]].emplace_back(d, u);
    		for (int v : g[u]) {
    			if (v != fa) dfs(v, u, d + 1);
    		}
    		--cnt[nums[u]];
    		cur[nums[u]].pop_back();
    	};
    	dfs(0, -1, 0);
    	return ans;
    }
};