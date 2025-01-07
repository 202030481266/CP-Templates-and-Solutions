// https://leetcode.cn/problems/find-minimum-time-to-finish-all-jobs/



// 超时的dfs
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
    	// 1 <= k <= jobs.length <= 12 
    	// 强NP问题 (bin packing problem)
    	int ans = 0, n = jobs.size(), f[k]; // 使用贪心算法生成一个比较好的解
    	memset(f, 0, sizeof(f));
    	sort(jobs.begin(), jobs.end(), greater<int>());
    	for (int i = 0; i < n; ++i) {
    		int mn = 0;
    		for (int j = 1; j < k; ++j) 
    			if (f[j] < f[mn]) mn = j;
    		f[mn] += jobs[i];
    	}
    	for (int i = 0; i < k; ++i) ans = max(ans, f[i]);
    	// dfs爆搜
    	memset(f, 0, sizeof(f));
    	function<void(int)> dfs = [&](int d) {
    		if (d == n) {
    			int tmp = 0;
    			for (int i = 0; i < k; ++i) tmp = (tmp > f[i] ? tmp : f[i]);
    			ans = (ans > tmp ? tmp : ans);
    			return;
    		}
    		// 分配这个工作给一个工人
    		for (int i = 0; i < k; ++i) {
    			if (f[i] + jobs[d] < ans) {
    				f[i] += jobs[d];
    				dfs(d + 1);
    				f[i] -= jobs[d];
    			}
    		}
    	};
    	dfs(0);
    	return ans;
    }
};



// 动态规划优化
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
    	int n = jobs.size(), dp[k][1 << n], ans = 0, f[k], g[1 << n];
    	memset(f, 0, sizeof(f));
    	memset(dp, -1, sizeof(dp));
    	memset(g, 0, sizeof(g));
    	// 贪心算法生成一个比较好的解
    	sort(jobs.begin(), jobs.end());
    	for (int i = 0; i < n; ++i) {
    		int mn = 0;
    		for (int j = 1; j < k; ++j) 
    			if (f[j] < f[mn]) mn = j;
    		f[mn] += jobs[i];
    	}
    	for (int i = 0; i < k; ++i) ans = max(ans, f[i]);
    	// 计算集合的时间
    	for (int i = 0; i < (1 << n); ++i) 
    		for (int j = 0; j < n; ++j) if ((i >> j) & 1) g[i] += jobs[j];
    	// dfs 爆搜
    	function<int(int, int)> dfs = [&](int p, int s) -> int {
    		// 给p分配工作
    		if (s == 0) return 0; // 没有工作可以分配
    		int &res = dp[p][s];
    		if (res != -1) return res;
    		if (p == k - 1) return dp[p][s] = g[s]; // 最后一个人必须全部承担
    		res = INT_MAX;
    		for (int sub = s; sub > 0; sub = (sub - 1) & s) 
    			if (g[sub] < ans)  
    				res = min(res, max(g[sub], dfs(p + 1, s ^ sub)));
    		return res;
    	};
    	return min(ans, dfs(0, (1 << n) - 1));
    }
};