// https://leetcode.cn/problems/painting-a-grid-with-three-different-colors/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int colorTheGrid(int m, int n) {
    	// 一般的dp是行不通的，很难找到状态转移的方法（状态直接使用整数表示，比如12321）
    	// 注意到这里的m最大为5，应该就是本题的突破口，3^5=243，但实际的合法状态更加少！
    	vector<int> status;
    	function<void(int, int)> dfs = [&](int d, int S) {
    		if (d == m) { status.emplace_back(S); return; }
    		for (int i = 1; i <= 3; ++i) 
    			if (S % 10 != i) dfs(d + 1, S * 10 + i);
    	};
    	dfs(0, 0); // 获取合法状态
    	// 检查两个合法状态是否能够对接
    	auto check = [&](int x, int y) -> bool {
    		string xs = to_string(x), ys = to_string(y);
    		for (int i = 0; i < m; ++i) 
    			if (xs[i] == ys[i]) return false;
    		return true;
    	};
    	int N = status.size();
    	vector f(n + 1, vector<int>(N));
    	vector<vector<int>> g(N);
    	// 构建图
    	for (int i = 0; i < N; ++i)
    		for (int j = i + 1; j < N; ++j) 
    			if (check(status[i], status[j])) {
    				g[i].emplace_back(j);
    				g[j].emplace_back(i);
    			}
    	for (int i = 0; i < N; ++i) f[1][i] = 1;
    	for (int i = 2; i <= n; ++i) {
    		for (int j = 0; j < N; ++j)
    			for (int v : g[j]) f[i][j] = (f[i][j] + f[i - 1][v]) % mod;
    	}
    	int ans = 0;
    	for (int i = 0; i < N; ++i) ans = (ans + f[n][i]) % mod;
    	return ans;
    }
};